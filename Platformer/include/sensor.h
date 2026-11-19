//
// Created by zoade on 05.11.2026.
//

#ifndef PLATFORMER_SENSOR_H
#define PLATFORMER_SENSOR_H
#include <box2d/box2d.h>
#include <string>
#include "constants.h"

class Sensor {
public:
    bool HasTouched = false;
    std::string name_;
    void Setup(b2BodyId body_id, float width, float height, float offset_x, float offset_y, std::string name);
};


#endif // PLATFORMER_SENSOR_H
