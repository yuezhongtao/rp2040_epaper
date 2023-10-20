cmake_minimum_required(VERSION 3.26)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

include(pico_extras_import.cmake)

# Pull in FreeRTOS
include(FreeRTOS_Kernel_import.cmake)

# https://github.com/FreeRTOS/FreeRTOS-Kernel
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM INTERFACE modules/freertos/include)
target_compile_definitions(freertos_config INTERFACE projCOVERAGE_TEST=0)

project(rp2040_epaper C CXX ASM)

set(CMAKE_C_STANDARD 23)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(rp2040_epaper app/main.c)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(rp2040_epaper pico_stdlib)

add_subdirectory(modules/depg0213_epd)
target_link_libraries(rp2040_epaper depg0213_epd)


# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(rp2040_epaper)

