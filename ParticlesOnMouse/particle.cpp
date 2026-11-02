//
// Created by zoade on 01.11.2026.
//

#include "particle.h"

// Constructor
Particle::Particle() {
    // Change the std::vector size to the number of particles
    points_.resize(max_particles_);
}

void Particle::SpawnParticleAtMouse(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        // setup position of particle
        points_[0] = {float(position.x), float(position.y)};

        // setup the vertices around it
        vertices_[0].position = {float(position.x) - width_/2 , float(position.y) - height_/2}; // top left
        vertices_[1].position = {float(position.x) + width_/2 , float(position.y) - height_/2}; // top right
        vertices_[2].position = {float(position.x) - width_/2 , float(position.y) + height_/2}; // bottom left
        vertices_[3].position = {float(position.x) + width_/2 , float(position.y) - height_/2}; // top right (again)
        vertices_[4].position = {float(position.x) + width_/2 , float(position.y) + height_/2}; // bottom right
        vertices_[5].position = {float(position.x) - width_/2 , float(position.y) + height_/2}; // bottom left (again)

        // make sure each vertex is white, NOT A COPY (could probably be written elsewhere...)
        for (sf::Vertex& vertex : vertices_) {
            vertex.color = sf::Color::White;
        }
    }
}

void Particle::Draw(sf::RenderWindow& window) {
    window.draw(vertices_);
}

// void Particle::Fall(float delta_time) {
//     if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
//         square_.move({0.f, 1000.f * delta_time});
//     }
// }