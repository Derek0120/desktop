cmake_minimum_required (VERSION 3.14.0)

set(DESKTOP_VERSION "1.0.0")
project("desktop" VERSION ${DESKTOP_VERSION})
set(CMAKE_CXX_STANDARD 17)
### Dependencies
add_subdirectory(third-party/spdlog)
add_subdirectory(common)

add_subdirectory(base)

