//
// Created by zoade on 05.11.2026.
//

#ifndef BOX2D_TESTS_SENSOR_H
#define BOX2D_TESTS_SENSOR_H
#include <box2d/box2d.h>

class Sensor {
public:
    bool HasTouched = false;
    void Setup(b2BodyId body_id, b2Vec2 halfsize);
};


#endif // BOX2D_TESTS_SENSOR_H
