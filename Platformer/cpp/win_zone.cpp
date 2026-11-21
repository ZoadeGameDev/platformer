//
// Created by zoade on 20.11.2026.
//

#include "../include/win_zone.h"
void WinZone::SetupSensors() {
    win_zone_.Setup(body_, width_, height_, 0, 0, "win_zone_");
    // Setup Win Zone
    if (!texture_.loadFromFile("../../Assets/Images/flag3.png")) {
        std::println("no texture");
    }
    visual_.setSize({width_*2.f, height_*2.f});
    visual_.setOrigin({width_*2.f/2, (height_+5)/2});
    visual_.setTexture(&texture_);
    // Debug Visual
    debug_visual_.setFillColor(sf::Color(0, 255, 0, 126));
}

bool WinZone::CheckBool() {
    return win_zone_.HasTouched;
}