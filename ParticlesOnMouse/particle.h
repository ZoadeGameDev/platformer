//
// Created by zoade on 02.11.2026.
//

#ifndef SFML_AND_VARIOUS_TEST_PARTICLE_H
#define SFML_AND_VARIOUS_TEST_PARTICLE_H
#include <SFML/Graphics.hpp>

struct Particle {
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    bool active_ = false;

};


#endif // SFML_AND_VARIOUS_TEST_PARTICLE_H
