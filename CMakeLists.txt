cmake_minimum_required(VERSION 3.13...3.27)

include(pico_sdk_import.cmake)

project(tyler C CXX ASM)

pico_sdk_init()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project root stays on the include path so vendor headers like
# "common/pimoroni_common.hpp" resolve the way Pimoroni expects.
include_directories(
  ${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory(common)
add_subdirectory(drivers)
add_subdirectory(libraries)

add_executable(tyler
    src/tyler.cpp
    src/morse.cpp
    src/servo/servo.cpp
)

target_include_directories(tyler PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(tyler pico_stdlib servo2040 button)

pico_add_extra_outputs(tyler)
