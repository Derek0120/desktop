cmake_minimum_required (VERSION 3.14.0)

project("Top")
set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIB ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
### Dependencies
add_subdirectory(third-party/spdlog)
add_subdirectory(common)

add_subdirectory(base)

add_subdirectory(main)
