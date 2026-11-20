//
// Created by zoade on 20.11.2026.
//

#include "../include/win_zone.h"
void WinZone::SetupSensors() {
    win_zone_.Setup(body_, width_, height_, 0, 0, "win_zone_");
    debug_visual_.setFillColor(sf::Color(0, 255, 0, 126));
}

bool WinZone::CheckBool() {
    return win_zone_.HasTouched;
}