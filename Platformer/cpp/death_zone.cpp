//
// Created by zoade on 20.11.2026.
//

#include "../include/death_zone.h"
void DeathZone::SetupSensors() {
    death_zone_.Setup(body_, width_, height_, 0, 0, "death_zone_");
    // Visual
    // Setup Death Zone
    if (!texture_.loadFromFile("../../Assets/Images/evilboxv3.png")) {
        std::println("no texture");
    }
    visual_.setSize({width_, height_});
    visual_.setOrigin({width_/2, height_/2});
    visual_.setTexture(&texture_);
    // Debug Visual
    debug_visual_.setFillColor(sf::Color(255, 0, 0, 126));
}

bool DeathZone::CheckBool() {
    return death_zone_.HasTouched;
}