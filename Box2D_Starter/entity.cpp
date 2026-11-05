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
}

void Entity::Update() {
    physics_.Update();
    sf::Vector2f newPosition;
    newPosition.x = Conversion::Pixels(physics_.GetPosition().x);
    newPosition.y = 600 - Conversion::Pixels(physics_.GetPosition().y);
    shape_.setPosition(newPosition);

}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(shape_, states);
}