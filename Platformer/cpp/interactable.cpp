//
// Created by zoade on 19.11.2026.
//

#include "../include/interactable.h"

void Interactable::Setup(b2WorldId& world, b2Vec2 position, float width, float height){
    // Physics
    width_ = width;
    height_ = height;
    // Setup Body
    b2BodyDef def = b2DefaultBodyDef();
    def.type =  b2_staticBody;
    def.position = position; // Initial position
    body_ = b2CreateBody(world, &def);

    // No material as this is only a holder for a sensor
    // Same goes for shape

    // Only visuals, since sensor doesn't do that on its own
    debug_visual_.setSize({width_, height_});
    debug_visual_.setOrigin({width_/2, height_/2});

    SetupSensors();
}

void Interactable::UpdateVisuals() {
    sf::Vector2f newPosition;
    newPosition.x = Conversion::Pixels(b2Body_GetPosition(body_).x);
    newPosition.y = 600 - Conversion::Pixels(b2Body_GetPosition(body_).y);
    // Debug Visual
    // Put the shapes togethers to form our visuals
    debug_visual_.setPosition(newPosition);
    //visual_bottom_circle_.setPosition({newPosition.x, newPosition.y + height_/2});
}

void Interactable::SetupSensors() {
    interactable_.Setup(body_, width_, height_, 0, 0, "interactable_");
}

void Interactable::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(debug_visual_, states);
}