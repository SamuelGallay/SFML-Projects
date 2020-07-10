# for Linux, BSD, Solaris, Minix
if(UNIX AND NOT APPLE)
  set(PLATFORM_SOURCES linux.cpp)

# for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
elseif(APPLE)
  set(PLATFORM_SOURCES macos.cpp)

# for Windows operating system in general
elseif(WIN32)
  set(PLATFORM_SOURCES windows.cpp)

# others
else()
  message(WARNING "Platform not supported")
endif()

add_library(engine_lib engine.cpp utilitary.cpp ${PLATFORM_SOURCES})

target_link_libraries(engine_lib PUBLIC sfml-graphics sfml-audio)

target_include_directories(engine_lib PUBLIC .)
