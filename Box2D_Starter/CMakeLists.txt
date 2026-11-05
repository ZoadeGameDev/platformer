add_executable(Box2D_Starter main.cpp
        game.cpp
        game.h
        physicalobject.cpp
        physicalobject.h
        entity.cpp
        entity.h
        constants.h
)

target_link_libraries(Box2D_Starter PUBLIC SFML::Graphics box2d::box2d)