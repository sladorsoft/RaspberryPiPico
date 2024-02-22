#include <pico/stdlib.h>
#include <FreeRTOS.h>
#include <task.h>


void vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName)
{
    panic("Stack overflow. Task: %s\n", pcTaskName);
}

void vApplicationMallocFailedHook()
{
    panic("malloc failed");
}

static void ledTask(void* pvParameters)
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (true)
    {
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    stdio_init_all();
    
    xTaskCreate(ledTask, "LED", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    vTaskStartScheduler(); 
    panic_unsupported();
}
