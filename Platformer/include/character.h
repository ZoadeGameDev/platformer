//
// Created by zoade on 09.11.2026.
//

#ifndef PLATFORMER_CHARACTER_H
#define PLATFORMER_CHARACTER_H
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <print>
#include "constants.h"
#include "sensor.h"


class Character : public sf::Drawable {
public:
    void Setup(b2WorldId& world, b2Vec2 position, float width, float height);

    void UpdateVisuals();

    void CharacterStates(double dt);
    void CharacterEvents(std::optional<sf::Event> event);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    void SetVelocity(std::optional<float> velocity_x, std::optional<float> velocity_y);

    void AddVelocity(std::optional<float> velocity_x, std::optional<float> velocity_y, float max_velocity_x, float max_velocity_y);
    void SubstractVelocity(std::optional<float> velocity_x, std::optional<float> velocity_y, float max_velocity_x, float max_velocity_y);

    void SetupDebugVisual();

    // Physics
    b2BodyId body_;
    float width_;
    float height_;
    float speed_ = 3.f;
    float max_speed_ = 10;
    float jump_buffer_ = kJumpBufferMax_;
    const float kJumpBufferMax_ =  0.25f;
    float coyote_time_ = kCoyoteTimeMax_;
    const float kCoyoteTimeMax_ = 0.2f;
    // Sensor
    Sensor grounded_;
    float grounded_offset_y_;
    float grounded_width_;
    float grounded_height_;
    sf::RectangleShape visual_grounded_;
    // Visuals
    // Debug Visuals
    bool show_debug_visuals_ = true;
    sf::RectangleShape visual_rectangle_;
    sf::CircleShape visual_top_circle_;
    sf::CircleShape visual_bottom_circle_;
};


#endif // PLATFORMER_CHARACTER_H
