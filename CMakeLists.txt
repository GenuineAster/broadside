cmake_minimum_required(VERSION 2.8)

project(broadside)

# Set options
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type ( Debug / Release )" FORCE)
endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

# Add a place to look for CMake modules in
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules;${CMAKE_MODULE_PATH}")

# Add source files
set(SRC_DIR "src")
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SRC_DIR}/*)

include_directories(${SRC_DIR})

#find_package(GLFW)
#include_directories(${GLFW_INCLUDE_DIRS})
#link_libraries(${GLFW_LIBRARIES})

#find_package(GLEW)
#include_directories(${GLEW_INCLUDE_DIRS})
#link_libraries(${GLEW_LIBRARIES})

#find_package(OpenGL)
#include_directories(${OPENGL_INCLUDE_DIRS})
#link_libraries(${OPENGL_LIBRARIES})

#find_package(Assimp)
#include_directories(${ASSIMP_INCLUDE_DIRS})
#link_libraries(${ASSIMP_LIBRARIES})


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpmath=sse -msse3")
endif()

# Enable C++14
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic -mfpmath=sse -msse3 -pthread")
endif()

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})


install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin/)
install(DIRECTORY assets DESTINATION ${CMAKE_BINARY_DIR})
