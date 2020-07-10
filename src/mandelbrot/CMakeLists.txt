add_library(mandelbrot_lib Mandelbrot.cpp MandelbrotState.cpp GUI.cpp)

target_link_libraries(mandelbrot_lib PRIVATE engine_lib sfml-graphics ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(mandelbrot_lib PUBLIC .)
