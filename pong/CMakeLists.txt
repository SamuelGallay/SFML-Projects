add_executable(Pong main.cpp application.cpp gameState.cpp introState.cpp menuState.cpp particles.cpp state.cpp stateMachine.cpp resourceHolder.cpp)

target_link_libraries(Pong sfml-graphics sfml-audio)

install(TARGETS Pong DESTINATION .)
