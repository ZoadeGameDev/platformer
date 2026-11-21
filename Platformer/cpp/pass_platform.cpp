//
// Created by zoade on 19.11.2026.
//

#include "../include/pass_platform.h"

void PassPlatform::SetupSensors() {
    pass_.Setup(body_, width_, height_, 0, 0, "pass_");
    // Visual
    // Setup Pass Platform
    if (!texture_.loadFromFile("../../Assets/Images/platform.png")) {
        std::println("no texture");
    }
    visual_.setSize({width_, height_});
    visual_.setOrigin({width_/2, height_/2});
    visual_.setTexture(&texture_);
    // Debug Visual
    debug_visual_.setSize({width_, height_});
    debug_visual_.setOrigin({width_/2, height_/2});
    debug_visual_.setFillColor(sf::Color(255, 255, 255, 126));
}
