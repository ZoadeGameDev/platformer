//
// Created by zoade on 12.11.2026.
//

#ifndef PLATFORMER_PLATFORM_BLOCK_H
#define PLATFORMER_PLATFORM_BLOCK_H
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <print>
#include "constants.h"
#include "settings.h"
#include "sensor.h"

class Platform : public sf::Drawable {
public:
    void Setup(b2WorldId& world, b2Vec2 position, float width, float height);

    void UpdateVisuals();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:
    virtual void  SetupSensors();

    void SetupDebugVisual();

    // Physics
    b2BodyId body_;
    float width_;
    float height_;
    // Visuals
    sf::Texture texture_;
    sf::RectangleShape visual_;
    // Debug Visuals
    sf::RectangleShape debug_visual_;
private:
    // Sensor
    Sensor ground_;
};


#endif // PLATFORMER_PLATFORM_BLOCK_H
