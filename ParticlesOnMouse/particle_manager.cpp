//
// Created by zoade on 01.11.2026.
//

#include "particle_manager.h"

// Constructor
ParticleManager::ParticleManager() {
    // Change the std::vector size to the number of particles
    p_list_.resize(max_particles_);
}

void ParticleManager::SpawnParticleAtMouse(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        // setup position of particle
       p_list_[0].position_ = {float(position.x), float(position.y)};
    }
}

void ParticleManager::Draw(sf::RenderWindow& window) {
    // setup the vertices around the position of the particule
    vertices_[0].position = {p_list_[0].position_.x - width_/2 , p_list_[0].position_.y - height_/2}; // top left
    vertices_[1].position = {p_list_[0].position_.x + width_/2 , p_list_[0].position_.y - height_/2}; // top right
    vertices_[2].position = {p_list_[0].position_.x - width_/2 , p_list_[0].position_.y + height_/2}; // bottom left
    vertices_[3].position = {p_list_[0].position_.x + width_/2 , p_list_[0].position_.y - height_/2}; // top right (again)
    vertices_[4].position = {p_list_[0].position_.x + width_/2 , p_list_[0].position_.y + height_/2}; // bottom right
    vertices_[5].position = {p_list_[0].position_.x - width_/2 , p_list_[0].position_.y + height_/2}; // bottom left (again)

    // make sure each vertex is white, NOT A COPY (could probably be written elsewhere...)
    for (sf::Vertex& vertex : vertices_) {
        vertex.color = sf::Color::White;
    }
    window.draw(vertices_);
}

void ParticleManager::Fall(float delta_time) {
    for (Particle& particle : p_list_) {
        particle.position_ += {0, 1000 * delta_time};
        std::println("x : {}, y : {}", particle.position_.x, particle.position_.y);
    }
}