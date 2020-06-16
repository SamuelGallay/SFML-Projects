add_executable(Example main.cpp MenuState.cpp)

target_link_libraries(Example sfml-graphics engine_lib space_lib brownian_lib)

install(TARGETS Example DESTINATION .)
