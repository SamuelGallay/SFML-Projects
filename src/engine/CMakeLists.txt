add_library(engine_lib Button.cpp GameEngine.cpp State.cpp ResourceHolder.cpp)

target_link_libraries(engine_lib PRIVATE app1::rc sfml-graphics)

target_include_directories(engine_lib PUBLIC .)

install(TARGETS engine_lib DESTINATION .)
