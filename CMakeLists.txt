cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)

project(SFML-Projects)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(Threads)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Ofast")

add_subdirectory(space)
add_subdirectory(mandelbrot)
add_subdirectory(fantasy)
add_subdirectory(brownian)
add_subdirectory(pong)
add_subdirectory(engine)

install(DIRECTORY media DESTINATION .)
