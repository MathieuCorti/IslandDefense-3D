cmake_minimum_required(VERSION 3.10)
project(IslandDefense3D)

set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(IslandDefense3D
        
        main.cpp

        srcs/Game.cpp
        srcs/includes/Game.hpp
        srcs/helpers/Displayable.hpp
        srcs/helpers/Shape.hpp
        srcs/helpers/Entity.hpp
        srcs/helpers/Movable.hpp
        srcs/helpers/Axes.hpp
        srcs/helpers/Glut.hpp
        srcs/helpers/Color.hpp
        srcs/helpers/Alive.hpp
        srcs/UI.cpp
        srcs/includes/UI.hpp
        srcs/includes/Entities.hpp
        srcs/Shape.cpp
        srcs/Displayable.cpp
        srcs/Movable.cpp
        srcs/includes/Config.hpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(IslandDefense3D ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})