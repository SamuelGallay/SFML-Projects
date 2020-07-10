add_executable(Menu main.cpp MenuState.cpp Button.cpp)

target_link_libraries(Menu
  engine_lib
  space_lib
  brownian_lib
  pong_lib
  mandelbrot_lib
  fantasy_lib
  )
