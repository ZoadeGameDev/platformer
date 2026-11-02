//
// Created by zoade on 01.11.2026.
//

#ifndef SFML_AND_VARIOUS_TEST_SQUARE_H
#define SFML_AND_VARIOUS_TEST_SQUARE_H
#include <SFML/Graphics.hpp>
#include <random>
#include <print>
#include "particle.h"


class ParticleManager {
public:
    //Constructor
    ParticleManager();
    void SpawnParticleAtMouse(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    void Fall(float delta_time);
private:
    float width_ = 25.f;
    float height_ = 25.f;
    int max_particles_ = 10000;

    float limit_ = 540.f; // default is 542
    sf::RectangleShape line_ = sf::RectangleShape(sf::Vector2f(1000, 1));

    std::vector<Particle> p_list_;
    sf::VertexArray vertices_ = sf::VertexArray(sf::PrimitiveType::Triangles, 6 * max_particles_);

    std::vector<sf::Color> color_list_ = {sf::Color::Red, sf::Color::Green, sf::Color::Blue};
};


#endif // SFML_AND_VARIOUS_TEST_SQUARE_H
