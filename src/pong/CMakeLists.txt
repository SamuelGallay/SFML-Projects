add_library(pong_lib PongState.cpp ParticleSystem.cpp)

target_link_libraries(pong_lib PRIVATE engine_lib)

target_include_directories(pong_lib PUBLIC .)
