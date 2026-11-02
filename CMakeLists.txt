cmake_minimum_required(VERSION 4.3)
project(sfml_and_various_tests)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML COMPONENTS Audio Graphics Window System  CONFIG REQUIRED)

add_subdirectory(MovingCharacter)
add_subdirectory(ParticlesOnMouse)
add_subdirectory(ShowingInputs)
add_subdirectory(SquareOnMouse)