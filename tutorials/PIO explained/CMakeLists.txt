cmake_minimum_required(VERSION 3.15)

# The name of our project
set(PROJECT_NAME WS2812)

# The board name. Use one of the header file names from "${PICO_SDK_PATH}/src/boards/include/boards"
# Official Pico boards are:
# pico, pico_w, pico2, pico2_w
set(PICO_BOARD pico)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

project(${PROJECT_NAME} C CXX)
set(TARGET_NAME ${PROJECT_NAME})


add_executable(${TARGET_NAME}
    WS2812.c
)

target_compile_definitions(${TARGET_NAME} PRIVATE
)

target_include_directories(${TARGET_NAME} PRIVATE
)

target_link_libraries(${TARGET_NAME} PRIVATE
    pico_stdlib
    hardware_pio
    hardware_dma
)

pico_add_extra_outputs(${TARGET_NAME})

pico_enable_stdio_uart(${TARGET_NAME} 1)
#pico_enable_stdio_usb(${TARGET_NAME} 1)

pico_generate_pio_header(${TARGET_NAME} ${CMAKE_CURRENT_LIST_DIR}/ws2812a.pio)
pico_generate_pio_header(${TARGET_NAME} ${CMAKE_CURRENT_LIST_DIR}/ws2812b.pio)
pico_generate_pio_header(${TARGET_NAME} ${CMAKE_CURRENT_LIST_DIR}/ws2812c.pio)
pico_generate_pio_header(${TARGET_NAME} ${CMAKE_CURRENT_LIST_DIR}/ws2812d.pio)
