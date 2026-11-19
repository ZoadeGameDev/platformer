//
// Created by zoade on 05.11.2026.
//

#ifndef PLATFORMER_CONTACTS_H
#define PLATFORMER_CONTACTS_H
#include <box2d/box2d.h>
#include <print>
#include "sensor.h"

bool no_collision = false;

bool SolidContact(b2ShapeId shapeIdA, b2ShapeId shapeIdB, b2Manifold* manifold, void* context) {
    // if (no_collision) {
    //     return false;
    // }
    //
    // return true;

    return !no_collision;

}

void SensorsContact(b2WorldId worldId) {
    const b2SensorEvents sensors = b2World_GetSensorEvents(worldId);

    for (int i = 0; i < sensors.beginCount; ++i) {
        const b2SensorBeginTouchEvent& e = sensors.beginEvents[i];

        // Les deux formes portent un `Objet*` : le cast est sur, et chacune
        // sait ce qu'elle a touche grace a l'etiquette de l'autre.
        auto* a = static_cast<Sensor*>(b2Shape_GetUserData(e.sensorShapeId));
        auto* b = static_cast<Sensor*>(b2Shape_GetUserData(e.visitorShapeId));

        if (a) {
            std::println("a touched");
            a->HasTouched  = true;
        }
        if (b) {
            std::println("b touched");
            b->HasTouched  = true;
        }
        if (a && b) {
            if (a->name_ == "pass_" && b->name_ == "head_") {
                no_collision = true;
            }
            else if (a->name_ == "ground_" && b->name_ == "head_") {
                no_collision = false;
            }
            else if ((a->name_ == "pass_" && b->name_ == "grounded_") ||(a->name_ == "ground_" && b->name_ == "grounded_")) {
                no_collision = false;
            }
        }

    }


    for (int i = 0; i < sensors.endCount; ++i) {
        const b2SensorEndTouchEvent &e = sensors.endEvents[i];

        // Les deux formes portent un `Objet*` : le cast est sur, et chacune
        // sait ce qu'elle a touche grace a l'etiquette de l'autre.
        auto* a = static_cast<Sensor*>(b2Shape_GetUserData(e.sensorShapeId));
        auto* b = static_cast<Sensor*>(b2Shape_GetUserData(e.visitorShapeId));

        if (a) {
            a->HasTouched  = false;
        }
        if (b) {
            b->HasTouched  = false;
        }
    }

}



#endif // PLATFORMER_CONTACTS_H
