//
// Created by zoade on 01.11.2026.
//

#ifndef SFML_AND_VARIOUS_TEST_SQUARE_H
#define SFML_AND_VARIOUS_TEST_SQUARE_H
#include <SFML/Graphics.hpp>
#include <print>


class Square {
public:
    //Constructor
    Square();
    void SpawnSquareAtMouse(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    void Fall(float delta_time);
private:
    float width_ = 100.f;
    float height_ = 100.f;
    sf::RectangleShape square_ = sf::RectangleShape(sf::Vector2f(width_, height_));
    sf::Color color_ = sf::Color::White;
};


#endif // SFML_AND_VARIOUS_TEST_SQUARE_H
