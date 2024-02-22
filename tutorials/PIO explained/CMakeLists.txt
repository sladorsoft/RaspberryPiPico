# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(WS2812 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(WS2812 WS2812.c )

pico_set_program_name(WS2812 "WS2812")
pico_set_program_version(WS2812 "0.1")

pico_enable_stdio_uart(WS2812 1)
pico_enable_stdio_usb(WS2812 0)

pico_generate_pio_header(WS2812 ${CMAKE_CURRENT_LIST_DIR}/ws2812a.pio)
pico_generate_pio_header(WS2812 ${CMAKE_CURRENT_LIST_DIR}/ws2812b.pio)
pico_generate_pio_header(WS2812 ${CMAKE_CURRENT_LIST_DIR}/ws2812c.pio)
pico_generate_pio_header(WS2812 ${CMAKE_CURRENT_LIST_DIR}/ws2812d.pio)

# Add the standard library to the build
target_link_libraries(WS2812
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(WS2812 PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(WS2812
        hardware_pio
        hardware_dma
)

pico_add_extra_outputs(WS2812)
