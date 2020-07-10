cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

project(SFML-Projects)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)
find_package(Threads)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Ofast")

install(DIRECTORY media DESTINATION .)

add_subdirectory(src)
