//
// Created by zoade on 04.11.2026.
//

#include "physicalobject.h"

void PhysicalObject::Setup(b2WorldId& world, b2BodyType type, b2Vec2 position) {
    // def du corp
    def_ = b2DefaultBodyDef();
    def_.type = type;
    // changements du corp
    def_.position = position;
    // creation du corp
    body_ = b2CreateBody(world, &def_);

    // Forme
    // - Cercle -
    // b2Circle circle{};
    // circle.center = {0.0f, 0.0f};
    // circle.radius = 1.0f;
    // - Carree -
    b2Polygon square = b2MakeSquare(0.5f);


    // Matiere
    shape_def_ = b2DefaultShapeDef();
    shape_def_.density = 1.0f;
    shape_def_.material.friction = 0.0f;
    shape_def_.material.restitution = 0.0f;

    // Creation
    //b2CreateCircleShape(body_, &shape_def_, &circle);
    b2CreatePolygonShape(body_, &shape_def_, &square);

    // Setup et changement de la masse de l'objet
    b2MassData myMassData;
    myMassData.mass = 5.0f;
    myMassData.center = {0.0f, 0.0f};
    myMassData.rotationalInertia = 0.0f;
    b2Body_SetMassData(body_, myMassData);
}

void PhysicalObject::Update() {
    b2Vec2 body_position = b2Body_GetPosition(body_);
    std::println("x: {}, y : {}", body_position.x, body_position.y);
}

