add_executable(Brownian main.cpp)

target_link_libraries(Brownian sfml-graphics)

install(TARGETS Brownian DESTINATION .)
