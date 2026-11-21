//
// Created by zoade on 29.10.2026.
//

#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include <vector>
#include "character.h"
#include "contacts.h"
#include "platform.h"
#include "pass_platform.h"
#include "jump_star.h"
#include "flag.h"
#include "death_zone.h"
#include "win_zone.h"

class Game {
public:
    void BeginSetup();

    void Loop();

private:
    void GameEvents();

    //void CheckIfWindowClosed(const std::optional<sf::Event> &event);

    // Variables
    // Window variables
    sf::RenderWindow window;
    int frame_rate_ = Settings::fps_; // Technically frame_rate_limit but oh well...
    // World variables
    b2WorldId world_;

    const float kStep_ = 1.f / static_cast<float>(frame_rate_);
    const int kSubStep_ = 4;
    double accumulator_ = 0.0f;

};


#endif // PLATFORMER_TEST_GAME_H
