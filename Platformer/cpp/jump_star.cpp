//
// Created by zoade on 19.11.2026.
//

#include "../include/jump_star.h"

void JumpStar::SetupSensors() {
    jump_star_.Setup(body_, width_, height_, 0, 0, "jump_star_");
}