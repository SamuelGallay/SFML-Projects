add_executable(Menu main.cpp MenuState.cpp Button.cpp)

set_target_properties(Menu PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

target_link_libraries(Menu
  engine_lib
  space_lib
  brownian_lib
  pong_lib
  mandelbrot_lib
  fantasy_lib
  )

install(TARGETS Menu DESTINATION .)
