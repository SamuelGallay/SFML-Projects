add_executable(Space main.cpp Physical.cpp Planet.cpp Spaceship.cpp)

target_link_libraries(Space sfml-graphics)

install(TARGETS Space DESTINATION .)
