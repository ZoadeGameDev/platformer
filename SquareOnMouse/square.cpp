//
// Created by zoade on 01.11.2026.
//

#include "square.h"

//Constructor
Square::Square() {
    square_.setOrigin({width_ / 2.f, height_ / 2.f});
}
void Square::SpawnSquareAtMouse(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        square_.setPosition({float(position.x), float(position.y)});
    }
}

void Square::Draw(sf::RenderWindow& window) {
    window.draw(square_);
}

void Square::Fall(float delta_time) {
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        square_.move({0.f, 1000.f * delta_time});
    }
}