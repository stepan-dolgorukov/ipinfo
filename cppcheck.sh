#!/bin/bash

cppcheck include/ipinfo/*.hpp --std=c++20 \
                              --enable=all \
                              --platform=unix64

cppcheck src/ipinfo/*.cpp --std=c++20 \
                          --enable=all \
                          --platform=unix64
