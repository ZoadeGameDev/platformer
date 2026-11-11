//
// Created by zoade on 09.11.2026.
//

#ifndef BOX2D_TESTS_PHYSICALOBJECT_H
#define BOX2D_TESTS_PHYSICALOBJECT_H
#include <box2d/box2d.h>
#include <optional>


class PhysicalObject {
public:
    void PhysicsSetup(b2BodyType body_type);

private:
    // (I gave them all the possibility to be empty, to not put any values in them at initialization)
    //
    b2BodyId body_;
    b2BodyType body_type_ ;




};


#endif // BOX2D_TESTS_PHYSICALOBJECT_H
