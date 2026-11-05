//
// Created by zoade on 04.11.2026.
//

#include "entity.h"

#include "constants.h"

void Entity::Setup(sf::Color color, sf::Vector2f position, sf::Vector2f size) {
    shape_.setFillColor(color);
    shape_.setOutlineColor(sf::Color::White);
    shape_.setOutlineThickness(1);
    shape_.setOrigin({size.x/2, size.y/2});

    shape_.setPosition(position);

    shape_.setSize(size);
}

void Entity::SetupPhysics(b2WorldId& world, b2BodyType type, b2Vec2 position){
    physics_.Setup(world, type, position, {(Conversion::Meter(shape_.getSize().x))/2, (Conversion::Meter(shape_.getSize().y))/2});
    grounded_.Setup(physics_.GetBodyId(), {(Conversion::Meter(shape_.getSize().x))/2.0f, (Conversion::Meter(shape_.getSize().y))/2.0f});
}

void Entity::Update() {
    physics_.Update();
    sf::Vector2f newPosition;
    newPosition.x = Conversion::Pixels(physics_.GetPosition().x);
    newPosition.y = 600 - Conversion::Pixels(physics_.GetPosition().y);
    shape_.setPosition(newPosition);
    if (grounded_.HasTouched) {
        shape_.setFillColor(sf::Color::Green);
    } else {
        shape_.setFillColor(sf::Color::Red);
    }

}

void Entity::MoveLeft() {
    physics_.SetVelocity( -10.f, std::nullopt);
}

void Entity::MoveRight() {
    physics_.SetVelocity( 10.f, std::nullopt);
}

void Entity::Jump() {
    // if ( -0.1f < physics_.GetAcceleration().y && physics_.GetAcceleration().y < 0.1f) {
    //     physics_.SetVelocity( std::nullopt, 10);
    // }
    if (grounded_.HasTouched) {
        physics_.SetVelocity( std::nullopt, 10);
    }
}

void Entity::CancelMovement() {
    physics_.SetVelocity( 0.f, std::nullopt);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(shape_, states);
}

b2Vec2 Entity::GetAcceleration() {
    return physics_.GetAcceleration();
}

void Entity::SetAcceleration(float step) {
    physics_.SetAcceleration(step);
}

void Entity::SetOldVelocity() {
    physics_.SetOldVelocity();
}

void Entity::SetVelocity(std::optional<float> velocity_x, std::optional<float> velocity_y) {
    physics_.SetVelocity(velocity_x, velocity_y);
}