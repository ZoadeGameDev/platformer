//
// Created by zoade on 04.11.2026.
//

#include "entity.h"

void Entity::Setup(sf::Color color, sf::Vector2f position, sf::Vector2f size) {
    shape_.setFillColor(color);
    shape_.setOutlineColor(sf::Color::White);
    shape_.setOutlineThickness(1);
    shape_.setOrigin({size.x/2, size.y/2});

    shape_.setPosition(position);

    shape_.setSize(size);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(shape_, states);

}