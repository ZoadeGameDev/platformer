//
// Created by zoade on 01.11.2026.
//

#include "particle_manager.h"

// Constructor
ParticleManager::ParticleManager() {
    // Change the std::vector size to the number of particles
    p_list_.resize(max_particles_);

    // Setup the limit line
    line_.setPosition({0, limit_});

    // Setup base random for color
    srand(time(NULL));
}

void ParticleManager::SpawnParticleAtMouse(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        // setup position of particle
        for (Particle& particle : p_list_) {
            if (particle.active_ == false) {
                particle.active_ = true;
                particle.position_ = {float(position.x), float(position.y)};
                // new color for each particle
                particle.color_ = color_list_[rand() % color_list_.size()];
                //particle.color_  = sf::Color(rand() % 255, rand() % 255, rand() % 255);
                break;
            }
            }
    }
}

void ParticleManager::Draw(sf::RenderWindow& window) {
    for (int i = 0; i < max_particles_; i++) {
        int square_index = i * 6;
        // Visuals
        // setup the vertices around the position of the particule
        vertices_[square_index].position = {p_list_[i].position_.x - width_/2 , p_list_[i].position_.y - height_/2}; // top left
        vertices_[square_index + 1].position = {p_list_[i].position_.x + width_/2 , p_list_[i].position_.y - height_/2}; // top right
        vertices_[square_index + 2].position = {p_list_[i].position_.x - width_/2 , p_list_[i].position_.y + height_/2}; // bottom left
        vertices_[square_index + 3].position = {p_list_[i].position_.x + width_/2 , p_list_[i].position_.y - height_/2}; // top right (again)
        vertices_[square_index + 4].position = {p_list_[i].position_.x + width_/2 , p_list_[i].position_.y + height_/2}; // bottom right
        vertices_[square_index + 5].position = {p_list_[i].position_.x - width_/2 , p_list_[i].position_.y + height_/2}; // bottom left (again)
        // setup the color for each
        vertices_[square_index].color = p_list_[i].color_;
        vertices_[square_index + 1].color = p_list_[i].color_;
        vertices_[square_index + 2].color = p_list_[i].color_;
        vertices_[square_index + 3].color = p_list_[i].color_;
        vertices_[square_index + 4].color = p_list_[i].color_;
        vertices_[square_index + 5].color = p_list_[i].color_;
    }

    window.draw(vertices_);
    window.draw(line_);
}

void ParticleManager::Fall(float delta_time) {
    for (Particle& particle : p_list_) {
        if (particle.active_) {
            particle.position_ += {0, 1000 * delta_time};
            if (particle.position_.y > limit_) {
                particle.active_ = false;
            }
        }
    }
}