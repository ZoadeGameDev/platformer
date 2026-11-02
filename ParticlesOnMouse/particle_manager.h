//
// Created by zoade on 01.11.2026.
//

#ifndef SFML_AND_VARIOUS_TEST_SQUARE_H
#define SFML_AND_VARIOUS_TEST_SQUARE_H
#include <SFML/Graphics.hpp>
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
    float width_ = 100.f;
    float height_ = 100.f;
    int max_particles_ = 1;
    std::vector<Particle> p_list_;
    sf::VertexArray vertices_ = sf::VertexArray(sf::PrimitiveType::Triangles, 6);
    //sf::RectangleShape square_ = sf::RectangleShape(sf::Vector2f(width_, height_));
    sf::Color color_ = sf::Color::White;
};


#endif // SFML_AND_VARIOUS_TEST_SQUARE_H
