//
// Created by zoade on 05.11.2026.
//

#include "sensor.h"

void Sensor::Setup(b2BodyId body_id, b2Vec2 halfsize) {
    const b2Polygon box = b2MakeOffsetBox(halfsize.x, halfsize.y, {0.f,0.f}, b2Rot_identity);

    b2ShapeDef def = b2DefaultShapeDef();
    def.isSensor = true; // il détecte, il n'arrête rien
    def.enableSensorEvents = true; // sans ça : aucun événement
    def.userData = this; // Savoir qui c'est
    def.density = 0.f;

    b2CreatePolygonShape(body_id, &def, &box);
}