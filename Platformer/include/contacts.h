//
// Created by zoade on 05.11.2026.
//

#ifndef PLATFORMER_CONTACTS_H
#define PLATFORMER_CONTACTS_H
#include <box2d/box2d.h>
#include <print>
#include "settings.h"
#include "sensor.h"

bool no_collision = false;

bool SolidContact(b2ShapeId shapeIdA, b2ShapeId shapeIdB, b2Manifold* manifold, void* context) {
    if (Settings::i_am_on_passable_platforms_ && Settings::want_go_down_) {
        no_collision = true;
    }
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

        // if (a) {
        //     if (a->name_ != "heart_") {
        //         std::println("a touched");
        //         a->HasTouched  = true;
        //     }
        // }
        // if (b) {
        //     if (b->name_ != "heart_") {
        //         std::println("b touched");
        //         b->HasTouched  = true;
        //     }
        // }
        if (a && b) {
            if (a->name_ == "win_zone_" && b->name_ == "flag_detector_") {
                a->HasTouched  = true;
            }
            if (a->name_ == "jump_star_" && b->name_ == "jump_detector_") {
                b->HasTouched  = true;
            }
            if (a->name_ == "flag_" && b->name_ == "flag_detector_") {
                a->HasTouched  = true;
                b->HasTouched  = true;
            }
            if (a->name_ == "death_zone_" && b->name_ == "death_detector_") {
                b->HasTouched  = true;
            }
            if (a->name_ == "pass_" && b->name_ == "head_") {
                no_collision = true;
                b->HasTouched  = true;
            }
            else if (a->name_ == "ground_" && b->name_ == "head_") {
                no_collision = false;
                b->HasTouched  = false;
            }
            else if ((a->name_ == "pass_" && b->name_ == "grounded_") ||(a->name_ == "ground_" && b->name_ == "grounded_")) {
                if (a->name_ == "pass_") {
                    Settings::i_am_on_passable_platforms_ = true;
                    std::println("Im so AM passable rn");
                }
                else {
                    Settings::i_am_on_passable_platforms_ = false;
                    std::println("Im so NOT passable rn");
                }
                no_collision = false;
                b->HasTouched  = true;
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
            if (a->name_ != "flag_") {
                a->HasTouched  = false;
            }
        }
        if (b) {
            if (b->name_ != "flag_") {
                b->HasTouched  = false;
            }
        }
    }

}



#endif // PLATFORMER_CONTACTS_H
