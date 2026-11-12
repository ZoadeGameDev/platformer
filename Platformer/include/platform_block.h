//
// Created by zoade on 12.11.2026.
//

#ifndef PLATFORMER_PLATFORM_BLOCK_H
#define PLATFORMER_PLATFORM_BLOCK_H
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "constants.h"

class PlatformBlock : public sf::Drawable {
public:
    void Setup(b2WorldId& world, b2Vec2 position, float size);

    void UpdateVisuals();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    void SetupDebugVisual();

    // Physics
    b2BodyId body_;
    float size_;
    // Visuals
    sf::RectangleShape visual_;
};


#endif // PLATFORMER_PLATFORM_BLOCK_H
