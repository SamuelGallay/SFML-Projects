cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

project(SFML-Projects)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)
find_package(Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Ofast")


# Not Working Version
# file(DOWNLOAD "https://raw.githubusercontent.com/vector-of-bool/cmrc/master/CMakeRC.cmake" "${CMAKE_BINARY_DIR}/CMakeRC.cmake")
# include("${CMAKE_BINARY_DIR}/CMakeRC.cmake")
# cmrc_add_resource_library(
#     resources-holder

#     ALIAS holder::rc
#     NAMESPACE holder

#     media/FiraSans-Light.otf
#     media/spaceship.png
#     media/icon.png
#     media/ball.wav
#     media/fantasy.ogg
#     )

# Simple Working Version
install(DIRECTORY media DESTINATION .)

add_subdirectory(src)
