cmake_minimum_required (VERSION 3.14.0)

set(COMMON_VERSION "1.0.0")

project("common" VERSION ${COMMON_VERSION})

add_library(${PROJECT_NAME} SHARED)

#target_link_libraries(${PROJECT_NAME} INTERFACE SQLite::SQLite3)


file(GLOB_RECURSE COMMON_SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp ${CMAKE_CURRENT_LIST_DIR}/*.h)

target_sources(${PROJECT_NAME} 
	PRIVATE
    ${COMMON_SRC}
)

#target_include_directories(sqlite_orm INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
#target_link_libraries(${PROJECT_NAME} INTERFACE SQLite::SQLite3)

#target_compile_options(${PROJECT_NAME}
#	PRIVATE
#	-std=c++17
#)

target_include_directories(${PROJECT_NAME}
PRIVATE
 ${CMAKE_SOURCE_DIR}
 )

target_compile_definitions(${PROJECT_NAME} 
	PRIVATE
	COMMON_LIBRARY
)