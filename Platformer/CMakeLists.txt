add_executable(Platformer main.cpp
        cpp/game.cpp
        include/game.h
        cpp/character.cpp
        include/character.h
        cpp/platform.cpp
        include/platform.h
        cpp/sensor.cpp
        include/sensor.h
        include/contacts.h
)

target_link_libraries(Platformer PUBLIC SFML::Graphics box2d::box2d)