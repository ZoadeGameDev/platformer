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

    void ChangeCheckPointPosition(float x, float y);

    void UpdateVisuals();

    void CharacterStates(double dt);
    void CharacterEvents(std::optional<sf::Event> event);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void SetGameIsRunningFalse();

private:
    void SetVelocity(std::optional<float> velocity_x, std::optional<float> velocity_y);

    void AddVelocity(std::optional<float> velocity_x, std::optional<float> velocity_y, float max_velocity_x, float max_velocity_y);
    void SubstractVelocity(std::optional<float> velocity_x, std::optional<float> velocity_y, float max_velocity_x, float max_velocity_y);

    void SetupDebugVisual();

    // Physics
    b2BodyId body_;
    float width_;
    float height_;
    float speed_ = 5.f;
    float max_speed_ = 15;
    float jump_speed_ = 20; //22.5f;
    float jump_buffer_ = kJumpBufferMax_;
    const float kJumpBufferMax_ =  0.25f;
    float coyote_time_ = kCoyoteTimeMax_;
    const float kCoyoteTimeMax_ = 0.2f;
    bool can_jump_;
    float check_point_position_x_ = 0;
    float check_point_position_y_ = 0;
    bool game_is_running_ = true;
    // Sensor
    // grounded_
    Sensor grounded_;
    float grounded_offset_y_;
    float grounded_width_;
    float grounded_height_;
    sf::RectangleShape visual_grounded_;
    // head_
    Sensor head_;
    float head_offset_y_;
    float head_width_;
    float head_height_;
    sf::RectangleShape visual_head_;
    // all "core" detectors
    float core_width_;
    float core_height_;
    float core_offset_y_;
    sf::RectangleShape visual_core_;
    // jump_detector_
    Sensor jump_detector_;
    float jump_detector_width_;
    float jump_detector_height_;
    float jump_detector_offset_y_;
    // flag_detector_
    Sensor flag_detector_;
    float flag_detector_width_;
    float flag_detector_height_;
    float flag_detector_offset_y_;
    // flag_detector_
    Sensor death_detector_;
    float death_detector_width_;
    float death_detector_height_;
    float death_detector_offset_y_;
    // Visuals
    // Debug Visuals
    bool show_debug_visuals_ = true;
    sf::RectangleShape visual_rectangle_;
    sf::CircleShape visual_top_circle_;
    sf::CircleShape visual_bottom_circle_;
};


#endif // PLATFORMER_CHARACTER_H
