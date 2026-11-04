//
// Created by zoade on 04.11.2026.
//

#include "physicalobject.h"

void PhysicalObject::Setup(b2WorldId& world) {
    // def du corp
    def_ = b2DefaultBodyDef();
    def_.type = b2_dynamicBody;
    // changements du corp
    def_.position = {0.0f, 0.0f};
    // creation du corp
    body_ = b2CreateBody(world, &def_);

    // Forme
    // - Cercle -
    // b2Circle circle{};
    // circle.center = {0.0f, 0.0f};
    // circle.radius = 1.0f;
    // - Carree -
    b2Polygon square = b2MakeSquare(1.0f);


    // Matiere
    shape_def_ = b2DefaultShapeDef();
    shape_def_.density = 1.0f;
    shape_def_.material.friction = 1.0f;

    // Creation
    //b2CreateCircleShape(body_, &shape_def_, &circle);
    b2CreatePolygonShape(body_, &shape_def_, &square);
}

void PhysicalObject::Update() {
    b2Vec2 body_position = b2Body_GetPosition(body_);
    std::println("x: {}, y : {}", body_position.x, body_position.y);
}

