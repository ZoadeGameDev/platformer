//
// Created by zoade on 04.11.2026.
//

#ifndef BOX2D_TESTS_PHYSICAL_OBJECT_H
#define BOX2D_TESTS_PHYSICAL_OBJECT_H
#include <box2d/box2d.h>
#include <SFML/System.hpp>
#include <print>

class PhysicalObject {
public:
    void Setup(b2WorldId& world, b2BodyType type, b2Vec2 position, b2Vec2 halfsize);
    void Update();
    b2Vec2 GetPosition();
    b2Vec2 GetVelocity();
    b2Vec2 GetAcceleration();

    b2BodyId GetBodyId();

    void SetAcceleration(float step);
    void SetOldVelocity();
    void SetVelocity(std::optional<float> velocity_x, std::optional<float> velocity_y);


private:
    b2BodyDef def_;
    b2BodyId body_;
    b2ShapeDef shape_def_;

    b2Vec2 old_velocity_;
    b2Vec2 acceleration_;




};


#endif // BOX2D_TESTS_PHYSICAL_OBJECT_H
