add_library(space_lib Physical.cpp Planet.cpp Spaceship.cpp SpaceState.cpp)

target_link_libraries(space_lib PRIVATE sfml-graphics engine_lib)

target_include_directories(space_lib PUBLIC .)
