//
// Created by zoade on 05.11.2026.
//
#include <box2d/box2d.h>
#include <box2d/collision.h>
#include <box2d/id.h>
#include <box2d/types.h>
#include "../include/sensor.h"

void Sensor::Setup(b2BodyId body_id, float width, float height, float offset_x, float offset_y) {
    const b2Polygon box = b2MakeOffsetBox(Conversion::Meters(width/2), Conversion::Meters(height/2), {Conversion::Meters(offset_x),Conversion::Meters(offset_y)}, b2Rot_identity);

    b2ShapeDef def = b2DefaultShapeDef();
    def.isSensor = true; // il détecte, il n'arrête rien
    def.enableSensorEvents = true; // sans ça : aucun événement
    def.userData = this; // Savoir qui c'est
    def.density = 0.f;

    b2CreatePolygonShape(body_id, &def, &box);
}