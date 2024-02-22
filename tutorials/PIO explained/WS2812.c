#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "hardware/dma.h"

#include "ws2812a.pio.h"
#include "ws2812b.pio.h"
#include "ws2812c.pio.h"
#include "ws2812d.pio.h"


// uncomment one of these to use its implementation
//#define USE_WS2812A_PIO
//#define USE_WS2812B_PIO
//#define USE_WS2812C_PIO
#define USE_WS2812D_PIO

#define WS2812_PIN 15
#define LED_COUNT 11

uint32_t colours[LED_COUNT] = 
{
    0x00ACCC,
    0x1D5DC5,
    0x541ECB,
    0x9C1CEE,
    0xB30D8B,
    0xBC1303,
    0xD6AB01,
    0xBEFE00,
    0x69FF03,
    0x26FF00,
    0x00FF19
};

uint32_t led_buffer[LED_COUNT];


int main()
{
    PIO pio = pio0;
    const uint sm = 0;
    const int led_dma_chan = 0;

#ifdef USE_WS2812A_PIO
    uint offset = pio_add_program(pio, &ws2812a_program);
    ws2812a_program_init(pio, sm, offset, WS2812_PIN);
#elif defined USE_WS2812B_PIO
    uint offset = pio_add_program(pio, &ws2812b_program);
    ws2812b_program_init(pio, sm, offset, WS2812_PIN);
#elif defined USE_WS2812C_PIO
    uint offset = pio_add_program(pio, &ws2812c_program);
    ws2812c_program_init(pio, sm, offset, WS2812_PIN);
#else
    uint offset = pio_add_program(pio, &ws2812d_program);
    ws2812d_program_init(pio, sm, offset, WS2812_PIN);
#endif

    // initialise the used GPIO pin to LOW
    gpio_put(WS2812_PIN, false);

    // wait for the WS2812s to reset
    sleep_us(50);

    // configure DMA to copy the LED buffer to the PIO state machine's FIFO
    dma_channel_config dma_ch0 = dma_channel_get_default_config(led_dma_chan);
    channel_config_set_transfer_data_size(&dma_ch0, DMA_SIZE_32);
    channel_config_set_read_increment(&dma_ch0, true);
    channel_config_set_write_increment(&dma_ch0, false);
    channel_config_set_dreq(&dma_ch0, DREQ_PIO0_TX0);

    // run the state machine
    pio_sm_set_enabled(pio, sm, true);

#ifdef USE_WS2812D_PIO
    pio_sm_put_blocking(pio, sm, (LED_COUNT - 1));
#endif

    uint32_t first_colour = 0;
    while (true)
    {
#ifdef USE_WS2812D_PIO
        while (pio_interrupt_get(pio, 0));
#endif
        for (uint32_t i = 0; i < LED_COUNT; i++)
        {
            led_buffer[i] = colours[(i + first_colour) % LED_COUNT];
        }

        // initiate DMA transfer 
        dma_channel_configure(led_dma_chan, &dma_ch0, &pio->txf[sm], led_buffer, LED_COUNT, true);

        sleep_ms(500);
        first_colour = (first_colour + 1) % LED_COUNT;
    }

    return 0;
}
