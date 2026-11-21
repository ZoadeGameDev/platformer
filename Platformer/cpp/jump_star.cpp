//
// Created by zoade on 19.11.2026.
//

#include "../include/jump_star.h"

void JumpStar::SetupSensors() {
    jump_star_.Setup(body_, width_, height_, 0, 0, "jump_star_");
    // Visual
    // Setup Jump Star
    if (!texture_.loadFromFile("../../Assets/Images/orb.png")) {
        std::println("no texture");
    }
    visual_.setSize({width_*1.75f, height_*1.75f});
    visual_.setOrigin({width_*1.75f/2, height_*1.75f/2});
    visual_.setTexture(&texture_);
    // Debug Visual
    debug_visual_.setFillColor(sf::Color(0, 0, 255, 126));
}