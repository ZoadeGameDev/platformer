//
// Created by zoade on 19.11.2026.
//

#include "../include/flag.h"

void Flag::SetupSensors() {
    flag_.Setup(body_, width_, height_, 0, 0, "flag_");
    // Setup Flag
    if (!texture_.loadFromFile("../../Assets/Images/flag1.png")) {
        std::println("no texture");
    }
    visual_.setSize({width_*2.f, height_*2.f});
    visual_.setOrigin({width_*2.f/2, (height_+4)/2});
    visual_.setTexture(&texture_);
    // Debug Visual
    debug_visual_.setFillColor(sf::Color(160, 120, 255, 126));
    position_x_ = b2Body_GetPosition(body_).x;
    position_y_ = b2Body_GetPosition(body_).y;
}

void Flag::UpdateVisuals() {
    Interactable::UpdateVisuals();
    if (flag_.HasTouched){
        if (!texture_.loadFromFile("../../Assets/Images/flag2.png")) {
            std::println("no texture");
        }
        debug_visual_.setFillColor(sf::Color(255, 255, 0, 126));
        }
}

float Flag::GetPositionX() {
    return position_x_;
}
float Flag::GetPositionY() {
    return position_y_;
}

bool Flag::CheckBool() {
    return flag_.HasTouched;
}

void Flag::SetBool(bool boolean) {
    flag_.HasTouched = boolean;
}