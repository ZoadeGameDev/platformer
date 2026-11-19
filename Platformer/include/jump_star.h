//
// Created by zoade on 19.11.2026.
//

#ifndef PLATFORMER_JUMP_STAR_H
#define PLATFORMER_JUMP_STAR_H
#include "../include/interactable.h"

class JumpStar : public Interactable {
    void SetupSensors() override;

private:
    // Sensor
    Sensor jump_star_;
};


#endif // PLATFORMER_JUMP_STAR_H
