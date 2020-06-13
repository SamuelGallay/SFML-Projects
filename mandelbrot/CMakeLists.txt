add_executable(Mandelbrot main.cpp Mandelbrot.cpp Application.cpp GUI.cpp)

target_link_libraries(Mandelbrot sfml-graphics ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS Mandelbrot DESTINATION .)
