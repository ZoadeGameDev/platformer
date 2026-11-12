//
// Created by zoade on 12.11.2026.
//

#include "../include/platform_block.h"
void PlatformBlock::Setup(b2WorldId& world, b2Vec2 position, float size){
    // Physics
    size_ = size;
    // Setup Body
    b2BodyDef def = b2DefaultBodyDef();
    def.type =  b2_staticBody;
    def.position = position; // Initial position
    body_ = b2CreateBody(world, &def);

    // General Material for the whole body
    b2ShapeDef general_shape_def = b2DefaultShapeDef();
    general_shape_def.density = 1.0f;
    general_shape_def.material.friction = 0.0f;
    general_shape_def.material.restitution = 0.0f; // doesn't bounce.

    // Shapes
    // Rectangle
    b2Polygon rectangle = b2MakeBox(Conversion::Meters(size_/2), Conversion::Meters(size_/2));

    // Creation
    // - Base rectangle
    b2CreatePolygonShape(body_, &general_shape_def, &rectangle);

    visual_.setSize({size, size});
    visual_.setOrigin({size/2, size/2});
}

void PlatformBlock::UpdateVisuals() {
    sf::Vector2f newPosition;
    newPosition.x = Conversion::Pixels(b2Body_GetPosition(body_).x);
    newPosition.y = 600 - Conversion::Pixels(b2Body_GetPosition(body_).y);
    // Debug Visual
    // Put the shapes togethers to form our visuals
    visual_.setPosition(newPosition);
    //visual_bottom_circle_.setPosition({newPosition.x, newPosition.y + height_/2});
}

void PlatformBlock::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(visual_, states);
}