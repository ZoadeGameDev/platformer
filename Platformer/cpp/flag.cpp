//
// Created by zoade on 19.11.2026.
//

#include "../include/flag.h"

void Flag::SetupSensors() {
    flag_.Setup(body_, width_, height_, 0, 0, "flag_");
}

void Flag::UpdateVisuals() {
    Interactable::UpdateVisuals();
    if (flag_.HasTouched){
        debug_visual_.setFillColor(sf::Color::Yellow);
        }
    else {
        debug_visual_.setFillColor(sf::Color::White);
    }
}