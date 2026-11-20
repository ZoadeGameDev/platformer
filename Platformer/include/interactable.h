//
// Created by zoade on 19.11.2026.
//

#ifndef PLATFORMER_INTERACTABLE_H
#define PLATFORMER_INTERACTABLE_H
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "settings.h"
#include "sensor.h"

class Interactable : public sf::Drawable {
public:
    void Setup(b2WorldId& world, b2Vec2 position, float width, float height);

    virtual void UpdateVisuals();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:
    virtual void  SetupSensors();

    void SetupDebugVisual();

    // Physics
    b2BodyId body_;
    float width_;
    float height_;
    // Visuals
    sf::RectangleShape debug_visual_;
private:
    // Sensor
    Sensor interactable_;
};


#endif // PLATFORMER_INTERACTABLE_H
