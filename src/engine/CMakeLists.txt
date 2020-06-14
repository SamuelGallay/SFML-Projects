add_library(engine_lib Button.cpp GameEngine.cpp State.cpp ResourceHolder.cpp utilitary.cpp)

target_link_libraries(engine_lib PRIVATE holder::rc sfml-graphics)

target_include_directories(engine_lib PUBLIC .)

install(TARGETS engine_lib DESTINATION .)
