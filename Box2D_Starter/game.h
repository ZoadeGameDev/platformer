//
// Created by zoade on 29.10.2026.
//

#ifndef SFML_AND_VARIOUS_TEST_GAME_H
#define SFML_AND_VARIOUS_TEST_GAME_H
#include <SFML/Graphics.hpp>
#include <print>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include <cmath>
#include "physicalobject.h"
#include "entity.h"

class Game {
public:


    void BeginSetup();

    void Loop();

private:
    void CheckEvents();

    //void CheckIfWindowClosed(const std::optional<sf::Event> &event);

    sf::RenderWindow window;
    b2WorldId monde_;

};


#endif // SFML_AND_VARIOUS_TEST_GAME_H
