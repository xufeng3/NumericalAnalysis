cmake_minimum_required(VERSION 3.21)
project(cm2)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(cm2
        computationResult.cpp
        )

add_executable(cm3
        InitImpact.cpp
        )

add_executable(cm4
        test.cpp
)