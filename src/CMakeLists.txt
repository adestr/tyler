add_executable(tyler
    tyler.cpp
    morse.cpp
    servo/servo.cpp
)

target_include_directories(tyler PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(tyler pico_stdlib servo2040 button)

pico_add_extra_outputs(tyler)
