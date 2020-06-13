add_executable(Fantasy main.cpp Application.cpp Player.cpp Level.cpp TileMap.cpp ResourcePath.cpp Perlin.cpp)

target_link_libraries(Fantasy sfml-graphics sfml-audio)

install(TARGETS Fantasy DESTINATION .)
