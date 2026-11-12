//
// Created by zoade on 09.11.2026.
//

#ifndef PLATFORMER_CHARACTER_H
#define PLATFORMER_CHARACTER_H
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "constants.h"


class Character : public sf::Drawable {
public:
    void Setup(b2WorldId& world, b2Vec2 position, float width, float height);

    void UpdateVisuals();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    void SetupDebugVisual();

    // Physics
    b2BodyId body_;
    float width_;
    float height_;
    // Visuals
    // Debug Visuals
    sf::RectangleShape visual_rectangle_;
    sf::CircleShape visual_top_circle_;
    sf::CircleShape visual_bottom_circle_;
};


#endif // PLATFORMER_CHARACTER_H
