//
// Created by zoade on 12.11.2026.
//

#include "../include/platform.h"
void Platform::Setup(b2WorldId& world, b2Vec2 position, float width, float height){
    // Physics
    width_ = width;
    height_ = height;
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
    b2Polygon rectangle = b2MakeBox(Conversion::Meters(width_/2), Conversion::Meters(height_/2));

    // Creation
    // - Base rectangle
    b2CreatePolygonShape(body_, &general_shape_def, &rectangle);

    debug_visual_.setSize({width_, height_});
    debug_visual_.setOrigin({width_/2, height_/2});

    SetupSensors();
}

void Platform::UpdateVisuals() {
    sf::Vector2f newPosition;
    newPosition.x = Conversion::Pixels(b2Body_GetPosition(body_).x);
    newPosition.y = 1200 - Conversion::Pixels(b2Body_GetPosition(body_).y);
    // Debug Visual
    // Put the shapes togethers to form our visuals
   debug_visual_.setPosition(newPosition);
    //visual_bottom_circle_.setPosition({newPosition.x, newPosition.y + height_/2});
}

void Platform::SetupSensors() {
    ground_.Setup(body_, width_, height_, 0, 0, "ground_");
    debug_visual_.setFillColor(sf::Color(255, 255, 255, 126));
}

void Platform::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // Debug
    if (Settings::debug_mode_) {
        target.draw(debug_visual_, states);
    }
}