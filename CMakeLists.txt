cmake_minimum_required(VERSION 3.15)
project(MicroEX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(MicroEX
    main.cpp
    orderbook/Orderbook.cpp
    engine/MatchingEngine.cpp
)
