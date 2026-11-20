//
// Created by zoade on 19.11.2026.
//

#include "../include/pass_platform.h"

void PassPlatform::SetupSensors() {
    pass_.Setup(body_, width_, height_, 0, 0, "pass_");
    debug_visual_.setFillColor(sf::Color(255, 255, 255, 126));
}
