//
// Created by zoade on 04.11.2026.
//

#ifndef BOX2D_TESTS_ENTITY_H
#define BOX2D_TESTS_ENTITY_H
#include <SFML/Graphics.hpp>

class Entity : public sf:: Drawable {
private:
    sf::RectangleShape shape_;
    sf::Texture texture_;
public:
    void Setup(sf::Color color, sf::Vector2f position, sf::Vector2f size);
    // ON PEUT REMPLACER LE DRAW DE WINDOW
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};


#endif // BOX2D_TESTS_ENTITY_H
