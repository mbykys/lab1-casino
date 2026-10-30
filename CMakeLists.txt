cmake_minimum_required(VERSION 3.14)
project(RouletteSimulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(core src/Money.cpp src/RouletteNumber.cpp src/Player.cpp src/CasinoBank.cpp src/Table.cpp)

add_executable(casino_app main.cpp)

target_link_libraries(casino_app core)

enable_testing()
add_subdirectory(tests)

