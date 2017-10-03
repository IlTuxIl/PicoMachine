cmake_minimum_required(VERSION 3.5)
project(PicoMachine)

INCLUDE(FindPkgConfig)

file( GLOB gKit_SOURCES gKit/*.cpp )
file( GLOB Pico_SOURCES src/*.cpp )

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES ${gKit_SOURCES} ${Pico_SOURCES} src/ReadPicture.cpp src/ReadPicture.h src/Scene.cpp src/Scene.h src/GameObject.cpp src/GameObject.h src/Main.cpp src/Player.cpp src/Player.h src/OBB2D.cpp src/OBB2D.h src/Terrain.cpp src/Terrain.h src/CheckPoints.cpp src/CheckPoints.h src/Obstacle.cpp src/Obstacle.h)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(gKit ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
add_executable(PicoMachine ${SOURCE_FILES})
target_link_libraries(PicoMachine ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${GLEW_LIBRARY})
