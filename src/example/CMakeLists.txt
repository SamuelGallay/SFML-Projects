add_executable(Example main.cpp MenuState.cpp BrownianState.cpp)

target_link_libraries(Example sfml-graphics engine_lib)

install(TARGETS Example DESTINATION .)
