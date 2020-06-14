cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

project(SFML-Projects)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)
find_package(Threads)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Ofast")

# ------------ Download CmakeRC Resource compiler ----------------#

file(DOWNLOAD "https://raw.githubusercontent.com/vector-of-bool/cmrc/master/CMakeRC.cmake"
                 "${CMAKE_BINARY_DIR}/CMakeRC.cmake")
include("${CMAKE_BINARY_DIR}/CMakeRC.cmake")

#========== Targets Configurations ============#

cmrc_add_resource_library(
    app1-resources

    ALIAS app1::rc
    NAMESPACE app1

    media/FiraSans-Light.otf
    media/spaceship.png
    )



add_subdirectory(src)

install(DIRECTORY media DESTINATION .)
