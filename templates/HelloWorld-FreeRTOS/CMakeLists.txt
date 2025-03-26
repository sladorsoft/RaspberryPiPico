cmake_minimum_required(VERSION 3.15)

# The name of our project
set(PROJECT_NAME HelloWorld-FreeRTOS)

# The board name. Use one of the header file names from "${PICO_SDK_PATH}/src/boards/include/boards"
# Official Pico boards are:
# pico, pico_w, pico2, pico2_w
set(PICO_BOARD pico)

# To use a local copy of FreeRTOS and skip checking out the Git repo
# put the full path to it in either FREERTOS_KERNEL_PATH environment variable
# or in this line below and uncomment it:
#set(FREERTOS_KERNEL_PATH "THE_PATH_TO_FREE_RTOS")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()


# If the path to FreeRTOS is not provided, check it out from Git
if(NOT ENV{FREERTOS_KERNEL_PATH} AND NOT FREERTOS_KERNEL_PATH)
    set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS-Kernel)
    include(FetchContent)
    FetchContent_Declare(freertos_kernel
        GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
        GIT_TAG V11.2.0     # Use 'main' to check out the most current version
        SOURCE_DIR ${FREERTOS_KERNEL_PATH}
    )
    FetchContent_Populate(freertos_kernel)
endif()

include(FreeRTOS_Kernel_import.cmake)


project(${PROJECT_NAME} C CXX)
set(TARGET_NAME ${PROJECT_NAME})

# This is required to let FreeRTOS find our FreeRTOSConfig.h config file
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


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
    pico_multicore

    freertos_config
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap3
)

pico_add_extra_outputs(${TARGET_NAME})

pico_enable_stdio_uart(${TARGET_NAME} 1)
#pico_enable_stdio_usb(${TARGET_NAME} 1)
