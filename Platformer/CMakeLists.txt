add_executable(Platformer main.cpp
        cpp/game.cpp
        include/game.h
        cpp/character.cpp
        include/character.h
        cpp/platform_block.cpp
        include/platform_block.h
)

target_link_libraries(Platformer PUBLIC SFML::Graphics box2d::box2d)