//
// Created by zoade on 04.11.2026.
//

#ifndef BOX2D_TESTS_ENTITY_H
#define BOX2D_TESTS_ENTITY_H
#include <SFML/Graphics.hpp>
#include <print>
#include "physicalobject.h"

class Entity : public sf:: Drawable {
public:
    void Setup(sf::Color color, sf::Vector2f position, sf::Vector2f size);
    void SetupPhysics(b2WorldId& world, b2BodyType type, b2Vec2 position);
    // ON PEUT REMPLACER LE DRAW DE WINDOW
    void Update();

    void MoveLeft();
    void MoveRight();
    void Jump();
    void CancelMovement();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


    b2Vec2 GetAcceleration();
    void SetAcceleration(float step);
    void SetOldVelocity();
    void SetVelocity(std::optional<float> velocity_x, std::optional<float> velocity_y);
private:
    sf::RectangleShape shape_;
    sf::Texture texture_;
    PhysicalObject physics_;
};


#endif // BOX2D_TESTS_ENTITY_H
