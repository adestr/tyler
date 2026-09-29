cmake_minimum_required(VERSION 3.13...3.27)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(tyler C CXX ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory(lib)

add_executable(tyler
    tyler.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(tyler pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(tyler)

# Enable C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
