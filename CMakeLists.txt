cmake_minimum_required(VERSION 3.5)
project(IslandDefense3D)

set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_executable(IslandDefense3D

        main.cpp

        srcs/Game.cpp
        srcs/includes/Game.hpp
        srcs/helpers/Displayable.hpp
        srcs/helpers/Shape.hpp
        srcs/helpers/Entity.hpp
        srcs/helpers/Movable.hpp
        srcs/helpers/Glut.hpp
        srcs/helpers/Color.hpp
        srcs/helpers/Alive.hpp
        srcs/includes/Cannon.hpp
        srcs/Cannon.cpp
        srcs/Projectile.cpp
        srcs/includes/Projectile.hpp
        srcs/Pellet.cpp
        srcs/includes/Pellet.hpp
        srcs/UI.cpp
        srcs/includes/UI.hpp
        srcs/Shape.cpp
        srcs/Displayable.cpp
        srcs/Movable.cpp
        srcs/includes/Config.hpp
        srcs/helpers/Vector3f.hpp
        srcs/includes/Stats.hpp
        srcs/Camera.cpp
        srcs/includes/Camera.hpp
        srcs/Stats.cpp
        srcs/includes/Stats.hpp
        srcs/Waves.cpp
        srcs/includes/Waves.hpp
        srcs/helpers/Axes.hpp
        srcs/includes/Skybox.hpp
        srcs/Skybox.cpp
        srcs/helpers/SOIL.h
        srcs/Island.cpp
        srcs/includes/Island.hpp
        srcs/helpers/Perlin.hpp
        srcs/Boat.cpp
        srcs/includes/Boat.hpp
        srcs/Light.cpp
        srcs/includes/Light.hpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_library(SOIL SOIL)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(IslandDefense3D ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${SOIL})