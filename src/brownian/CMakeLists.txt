add_library(brownian_lib BrownianState.cpp)

target_link_libraries(brownian_lib PRIVATE sfml-graphics engine_lib)

target_include_directories(brownian_lib PUBLIC .)
