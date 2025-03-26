cmake_minimum_required(VERSION 3.15)

# The name of our project
set(PROJECT_NAME HelloWorld)

# The board name. Use one of the header file names from "${PICO_SDK_PATH}/src/boards/include/boards"
# Official Pico boards are:
# pico, pico_w, pico2, pico2_w
set(PICO_BOARD pico)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

project(${PROJECT_NAME} C CXX)
set(TARGET_NAME ${PROJECT_NAME})

add_executable(${TARGET_NAME}
    main.c
)

target_compile_definitions(${TARGET_NAME} PRIVATE
)

target_include_directories(${TARGET_NAME} PRIVATE
)

target_link_libraries(${TARGET_NAME} PRIVATE
    pico_stdlib
    hardware_gpio
)

pico_add_extra_outputs(${TARGET_NAME})

pico_enable_stdio_uart(${TARGET_NAME} 1)
#pico_enable_stdio_usb(${TARGET_NAME} 1)
