add_library(engine_lib engine.cpp utilitary.cpp)

# Not Working Version
#target_link_libraries(engine_lib PRIVATE holder::rc sfml-graphics sfml-audio)

# Simple Working Version
target_link_libraries(engine_lib PRIVATE sfml-graphics sfml-audio)

target_include_directories(engine_lib PUBLIC .)
