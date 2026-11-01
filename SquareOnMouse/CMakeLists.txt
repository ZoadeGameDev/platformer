add_executable(SquareOnMouse main.cpp
        game.cpp
        game.h
        square.cpp
        square.h
)

target_link_libraries(SquareOnMouse PUBLIC SFML::Graphics)