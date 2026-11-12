cmake_minimum_required(VERSION 4.3)
project(platformer)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML COMPONENTS Audio Graphics Window System  CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

add_subdirectory(MovingCharacter)
add_subdirectory(ParticlesOnMouse)
add_subdirectory(ShowingInputs)
add_subdirectory(SquareOnMouse)
add_subdirectory(Box2D_Starter)
add_subdirectory(Platformer)
