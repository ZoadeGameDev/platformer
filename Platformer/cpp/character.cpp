//
// Created by zoade on 09.11.2026.
//

#include "../include/character.h"
// Public
// We enter the width and the height in pixels (for ease of use) and then convert it into meters
void Character::Setup(b2WorldId& world, b2Vec2 position, float width, float height){
    // Physics
    width_ = width;
    height_ = height;
    // Setup Body
    b2BodyDef def = b2DefaultBodyDef();
    def.type =  b2_dynamicBody;
    def.position = position; // Initial position
    body_ = b2CreateBody(world, &def);

    // General Material for the whole body
    b2ShapeDef general_shape_def = b2DefaultShapeDef();
    general_shape_def.density = 1.0f;
    general_shape_def.material.friction = 0.0f;
    general_shape_def.material.restitution = 0.0f; // doesn't bounce.

    // Shapes
    // Rectangle
    b2Polygon rectangle = b2MakeBox(Conversion::Meters(width/2), Conversion::Meters(height/2));

    // Top Circle
    b2Circle top_circle = { {0.f, Conversion::Meters(height/2)}, Conversion::Meters(width/2)};

    // Bottom Circle
    //b2Circle bottom_circle = { {0.f, -height/2}, width/2};

    // Creation
    // - Base rectangle
    b2CreatePolygonShape(body_, &general_shape_def, &rectangle);
    // - Top circle
    b2CreateCircleShape(body_, &general_shape_def, &top_circle);
    // - Bottom circle
    //b2CreateCircleShape(body_, &general_shape_def, &top_circle);

    SetupDebugVisual();
}

void Character::UpdateVisuals() {
    sf::Vector2f newPosition;
    newPosition.x = Conversion::Pixels(b2Body_GetPosition(body_).x);
    newPosition.y = 600 - Conversion::Pixels(b2Body_GetPosition(body_).y);
    // Debug Visual
    // Put the shapes togethers to form our visuals
    visual_rectangle_.setPosition(newPosition);
    visual_top_circle_.setPosition({newPosition.x, newPosition.y - height_/2});
    //visual_bottom_circle_.setPosition({newPosition.x, newPosition.y + height_/2});
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(visual_rectangle_, states);
    target.draw(visual_top_circle_, states);
    //target.draw(visual_bottom_circle_, states);
}

// Private
// Create the generals visuals shapes
void Character::SetupDebugVisual() {
    // Rectangle
    visual_rectangle_.setSize({width_, height_});
    visual_rectangle_.setOrigin({width_/2, height_/2});

    // Circles
    visual_top_circle_.setRadius(width_/2);
    visual_top_circle_.setOrigin({width_/2, width_/2});

//     visual_bottom_circle_.setRadius(width_/2);
//     visual_bottom_circle_.setOrigin({width_/2, width_/2});

}