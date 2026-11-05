//
// Created by zoade on 04.11.2026.
//

#include "physicalobject.h"

void PhysicalObject::Setup(b2WorldId& world, b2BodyType type, b2Vec2 position, b2Vec2 halfsize) {
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
    b2Polygon square = b2MakeBox(halfsize.x, halfsize.y);


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
    //std::println("x: {}, y : {}", body_position.x, body_position.y);
}

b2Vec2 PhysicalObject::GetPosition() {
    return b2Body_GetPosition(body_);
}

b2Vec2 PhysicalObject::GetVelocity() {
    return b2Body_GetLinearVelocity(body_);
}

b2Vec2 PhysicalObject::GetAcceleration() {
    return acceleration_;
}

void PhysicalObject::SetAcceleration(float step) {
    acceleration_ = {((GetVelocity().x - old_velocity_.x)/step), ((GetVelocity().y - old_velocity_.y)/step)
};
}

void PhysicalObject::SetOldVelocity() {
    old_velocity_ = GetVelocity();
}

void PhysicalObject::SetVelocity(std::optional<float> velocity_x, std::optional<float> velocity_y) {
    float final_velocity_x;
    float final_velocity_y;
    if (velocity_x) {
        final_velocity_x = *velocity_x;
    }
    else {
        final_velocity_x = GetVelocity().x;
    }
    if (velocity_y) {
        final_velocity_y = *velocity_y;
    }
    else {
        final_velocity_y = GetVelocity().y;
    }

    b2Body_SetLinearVelocity(body_, {final_velocity_x, final_velocity_y});
}

