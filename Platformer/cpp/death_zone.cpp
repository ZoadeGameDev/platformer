//
// Created by zoade on 20.11.2026.
//

#include "../include/death_zone.h"
void DeathZone::SetupSensors() {
    death_zone_.Setup(body_, width_, height_, 0, 0, "death_zone_");
    debug_visual_.setFillColor(sf::Color::Red);
}
