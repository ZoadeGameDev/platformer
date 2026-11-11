add_executable(Platformer main.cpp
        cpp/game.cpp
        include/game.h
        cpp/physicalobject.cpp
        include/physicalobject.h
)

target_link_libraries(Platformer PUBLIC SFML::Graphics box2d::box2d)