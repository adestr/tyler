if(NOT TARGET plasma)
  include(${CMAKE_CURRENT_LIST_DIR}/../../drivers/ws2812/ws2812.cmake)
endif()

if(NOT TARGET servo)
  include(${CMAKE_CURRENT_LIST_DIR}/../../drivers/servo/servo.cmake)
endif()

if(NOT TARGET servo_cluster)
  include(${CMAKE_CURRENT_LIST_DIR}/../../drivers/servo/servo_cluster.cmake)
endif()

add_library(servo2040 INTERFACE)

target_include_directories(servo2040 INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Pull in pico libraries that we need
target_link_libraries(servo2040 INTERFACE pico_stdlib ws2812 servo servo_cluster)