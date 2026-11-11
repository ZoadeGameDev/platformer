//
// Created by zoade on 29.10.2026.
//

#ifndef SFML_AND_VARIOUS_TEST_GAME_H
#define SFML_AND_VARIOUS_TEST_GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>

class Game {
public:


    void BeginSetup();

    void Loop();

private:
    void WindowEvents();

    //void CheckIfWindowClosed(const std::optional<sf::Event> &event);

    // Variables
    // Window variables
    sf::RenderWindow window;
    int frame_rate_ = 60; // Technically frame_rate_limit but oh well...
    // World variables
    b2WorldId world_;
    const float  kStep_ = 1.f/static_cast<float>(frame_rate_);
    const int kSubStep_ = 4;
    double accumulator_ = 0.0f;

};


#endif // SFML_AND_VARIOUS_TEST_GAME_H
