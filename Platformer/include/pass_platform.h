//
// Created by zoade on 19.11.2026.
//

#ifndef PLATFORMER_PASS_PLATFORM_H
#define PLATFORMER_PASS_PLATFORM_H
#include <print>
#include "platform.h"


class PassPlatform : public Platform{
void SetupSensors() override;

private:
    // Sensor
    Sensor pass_;
};


#endif // PLATFORMER_PASS_PLATFORM_H
