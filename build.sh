#!/bin/bash

if [[ -d ./build ]]; then
    echo "Clearing existing build directory..."
    rm -r ./build/*
else
    echo "Creating build directory..."
    mkdir ./build
fi

cmake --preset pico-servo2040
cmake --build --preset pico-servo2040
