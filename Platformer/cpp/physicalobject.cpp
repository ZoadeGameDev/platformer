//
// Created by zoade on 09.11.2026.
//

#include "../include/physicalobject.h"

void PhysicalObject::PhysicsSetup(b2WorldId& world, b2BodyType body_type, b2Vec2 position){
    // Setup Body
    b2BodyDef def = b2DefaultBodyDef();
    def.type =  body_type;
    def.position = position; // Initial position
    body_ = b2CreateBody(world, &def);

    // Shape
    b2Polygon Polygon;






}