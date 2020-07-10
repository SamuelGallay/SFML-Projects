add_library(fantasy_lib FantasyState.cpp Player.cpp Level.cpp TileMap.cpp Perlin.cpp)

target_link_libraries(fantasy_lib PRIVATE engine_lib sfml-graphics sfml-audio)

target_include_directories(fantasy_lib PUBLIC .)
