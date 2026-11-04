//
// Created by zoade on 04.11.2026.
//

#ifndef BOX2D_TESTS_PHYSICAL_OBJECT_H
#define BOX2D_TESTS_PHYSICAL_OBJECT_H
#include <box2d/box2d.h>
#include <print>

class PhysicalObject {
public:
    void Setup(b2WorldId& world);
    void Update();
private:
    b2BodyDef def_;
    b2BodyId body_;
    b2ShapeDef shape_def_;




};


#endif // BOX2D_TESTS_PHYSICAL_OBJECT_H
