//
// Created by zoade on 09.11.2026.
//

#include "../include/character.h"
// Public
// We enter the width and the height in pixels (for ease of use) and then convert it into meters
void Character::Setup(b2WorldId& world, b2Vec2 position, float width, float height){
    if (!texture_.loadFromFile("../../Assets/Images/guy1.png")) {
        std::println("no texture");
    }
    // Physics
    // variables setup
    width_ = width;
    height_ = height;

    // Sensor grounded_
    grounded_width_ = width_/1.1f;
    grounded_height_ = width_/4.0f;
    grounded_offset_y_ = height_/2; // (Problem, the sensor doesn't always work, i try to fix it via offset but it doesn't work)a
    // Sensor head_
    // We usually keep it small to be safe and not cancel all collision (values at the right)
    // BUT for the game it's working with big one so... might as well use it
    head_width_ =  width_*1.1; //width_/1.1f;
    head_height_ = width_*1.2; //width_/2.0f;
    head_offset_y_ = height_/2; //height_/2 + width_/2;
    // Core Sensors
    core_width_ = height_/1.5f;
    core_height_ = height_/1.5f;
    core_offset_y_ = width_/6;
    // Sensor jump_detector_
    jump_detector_width_ = core_width_;
    jump_detector_height_ = core_height_;
    jump_detector_offset_y_ = core_offset_y_;
    // Sensor flag_detector_
    flag_detector_width_ = core_width_;
    flag_detector_height_ = core_height_;
    flag_detector_offset_y_ = core_offset_y_;
    // Sensor death_detector_
    death_detector_width_ = core_width_;
    death_detector_height_ = core_height_;
    death_detector_offset_y_ = core_offset_y_;

    // Setup Body
    b2BodyDef def = b2DefaultBodyDef();
    def.type =  b2_dynamicBody;
    def.position = position; // Initial position
    def.fixedRotation = true; // IMPORTANT TO NOT FALL OFF EDGES!!!!!!!!!! HAD TO LOOK IT UP
    body_ = b2CreateBody(world, &def);

    // General Material for the whole body
    b2ShapeDef general_shape_def = b2DefaultShapeDef();
    general_shape_def.density = 1.0f;
    general_shape_def.material.friction = 0.0f;
    general_shape_def.material.restitution = 0.0f; // doesn't bounce.
    general_shape_def.enablePreSolveEvents = true; // IMPORTANT TO LET US DECIDE HOW COLLISIONS WILL WORK FOR PASS THROUGH PLATFORMS!!!

    // Shapes
    // Rectangle
    b2Polygon rectangle = b2MakeBox(Conversion::Meters(width/2), Conversion::Meters(height/2));

    // Top Circle
    b2Circle top_circle = { {0.f, Conversion::Meters(height/2)}, Conversion::Meters(width/2)};

    // Bottom Circle
    //b2Circle bottom_circle = { {0.f, -height/2}, width/2};

    // Creation
    // - Base rectangle
    b2CreatePolygonShape(body_, &general_shape_def, &rectangle);
    // - Top circle
    b2CreateCircleShape(body_, &general_shape_def, &top_circle);
    // - Bottom circle
    //b2CreateCircleShape(body_, &general_shape_def, &top_circle);

    // Sensors
    // grounded_
    grounded_.Setup(body_, grounded_width_, (grounded_height_), 0, -grounded_offset_y_, "grounded_");
    // head_
    head_.Setup(body_, head_width_, (head_height_), 0, head_offset_y_, "head_");
    // jump_detector_
    jump_detector_.Setup(body_, jump_detector_width_, (jump_detector_height_), 0, jump_detector_offset_y_, "jump_detector_");
    // flag_detector_
    flag_detector_.Setup(body_, flag_detector_width_, (flag_detector_height_), 0, flag_detector_offset_y_, "flag_detector_");
    // death_detector_
    death_detector_.Setup(body_, death_detector_width_, (death_detector_height_), 0, death_detector_offset_y_, "death_detector_");
    SetupVisual();
}

void Character::ChangeCheckPointPosition(float x, float y) {
    check_point_position_x_  = x;
    check_point_position_y_ = y;
}


void Character::UpdateVisuals() {
    sf::Vector2f newPosition;
    newPosition.x = Conversion::Pixels(b2Body_GetPosition(body_).x);
    newPosition.y = 1200 - Conversion::Pixels(b2Body_GetPosition(body_).y);
    visual_character_.setPosition(newPosition);
    // Debug Visual
    // Put the shapes togethers to form our visuals
    visual_rectangle_.setPosition(newPosition);
    visual_top_circle_.setPosition({newPosition.x, newPosition.y - height_/2});
    //visual_bottom_circle_.setPosition({newPosition.x, newPosition.y + height_/2});
    visual_grounded_.setPosition({newPosition.x, newPosition.y + grounded_offset_y_});
    visual_head_.setPosition({newPosition.x, newPosition.y - head_offset_y_});
    visual_core_.setPosition({newPosition.x, newPosition.y - jump_detector_offset_y_});

}

void Character::CharacterStates(double dt) {
    if (game_is_running_) {
        // Horizontal Movement (state, all frames)
        const float joystick_x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X); // For Controller
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) || joystick_x > 20.f) {
            if (b2Body_GetLinearVelocity(body_).x < 0.f) {
                SetVelocity(0,std::nullopt );
            }
            AddVelocity(speed_, std::nullopt, max_speed_, max_speed_);
        } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) || joystick_x < -20.f) {
            if (b2Body_GetLinearVelocity(body_).x > 0.f) {
                SetVelocity(0,std::nullopt );
            }
            SubstractVelocity(-speed_, std::nullopt, -max_speed_, -max_speed_);
        } else {
            // by default the x velocity is at 0
            SetVelocity(0,std::nullopt );
        }

        // I WANNA GO THROUGH PLATFORMS
        const float joystick_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y); // For Controller
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) || joystick_x > 20.f) {
            Settings::want_go_down_ = true;
        }
        else {
            Settings::want_go_down_ = false;
        }

        // Buffer
        // Modify Buffers (conditions is here to make sure it doesn't go overboard with the values and leak)
        if (jump_buffer_ > 0) {
            jump_buffer_ -= dt;
        }
        if (coyote_time_ > 0) {
            coyote_time_ -= dt;
        }

        // Use Buffer
        // COYOTE TIME MUST CHECK IF IT IS ACTUALLY GOING UP OR NOT TO RESET, IF IT DOESN'T, IT CAN DOUBLE JUMP!!!!!!
        if (can_jump_ && b2Body_GetLinearVelocity(body_).y < 0.1f) {
            coyote_time_ = kCoyoteTimeMax_;
        }

        if (coyote_time_ > 0 && jump_buffer_ > 0) {
            // actual jump
            SetVelocity(std::nullopt, jump_speed_);
            jump_buffer_ = 0;
            coyote_time_ = 0;
        }

        // Better Gravity
        float current_y_vel = b2Body_GetLinearVelocity(body_).y;

        if (current_y_vel < -0.1f) {
            // FALLING
            b2Body_SetGravityScale(body_, 2.5f);
        }
        else if (!(current_y_vel > 0.1f || (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) || sf::Joystick::isButtonPressed(0, 0)))) {
            // CANCEL CURRENT JUMP
            b2Body_SetGravityScale(body_, 3.0f);
        }
        else {
            // ON GROUND, JUMPING
            b2Body_SetGravityScale(body_, 1.0f);
        }

        // update Sensor info
        if (grounded_.HasTouched) {
            visual_grounded_.setFillColor(sf::Color(0, 255, 0, 126));
            can_jump_ = true;
        } else {
            visual_grounded_.setFillColor(sf::Color(255, 0, 0, 126));
        }
        if (head_.HasTouched) {
            visual_head_.setFillColor(sf::Color(0, 255, 0, 126));
        } else {
            visual_head_.setFillColor(sf::Color(255, 0, 0, 126));
        }
        if (jump_detector_.HasTouched || flag_detector_.HasTouched) {
            visual_core_.setFillColor(sf::Color(0, 0, 255, 126));
            can_jump_ = true;
        } else {
            visual_core_.setFillColor(sf::Color(255, 100, 255, 126));

        }
        if (!jump_detector_.HasTouched && !grounded_.HasTouched && !death_detector_.HasTouched) {
            can_jump_ = false;
        }

        if (death_detector_.HasTouched) {
            b2Body_SetTransform(body_, {check_point_position_x_, check_point_position_y_}, b2Body_GetRotation(body_));
            // RESET VELOCITY OR THIS WILL BECOME LIKE A PORTAL-LIKE GAME
            SetVelocity(0,0);
        }
    }
    else {
        b2Body_SetGravityScale(body_, 0.f);
        SetVelocity(0.f, 0.f);
    }




}

void Character::CharacterEvents(std::optional<sf::Event> event) {
    if (game_is_running_) {
        // Vertical Movement (event, once)
        // jump
        if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == sf::Keyboard::Scancode::Space) {
                jump_buffer_ = kJumpBufferMax_;
            }
        }
        if (const auto* button = event->getIf<sf::Event::JoystickButtonPressed>()) {
            if (button->button == 0) {
                jump_buffer_ = kJumpBufferMax_;
            }
        }
        // cancel jump
        if (const auto* key = event->getIf<sf::Event::KeyReleased>()) {
            if (key->scancode == sf::Keyboard::Scancode::Space) {
                float current_y_vel = b2Body_GetLinearVelocity(body_).y;
                if (current_y_vel > 0.f) {
                    SetVelocity(std::nullopt, current_y_vel * 0.35F);
                }
            }
        }
        if (const auto* button = event->getIf<sf::Event::JoystickButtonReleased>()) {
            if (button->button == 0) {
                float current_y_vel = b2Body_GetLinearVelocity(body_).y;
                if (current_y_vel > 0.f) {
                    SetVelocity(std::nullopt, current_y_vel * 0.35F);
                }
            }
        }
    }
}



void Character::SetVelocity(std::optional<float> velocity_x, std::optional<float> velocity_y) {
    float final_velocity_x;
    float final_velocity_y;
    if (velocity_x) {
        final_velocity_x = *velocity_x;
    }
    else {
        final_velocity_x = b2Body_GetLinearVelocity(body_).x;
    }
    if (velocity_y) {
        final_velocity_y = *velocity_y;
    }
    else {
        final_velocity_y = b2Body_GetLinearVelocity(body_).y;
    }

    b2Body_SetLinearVelocity(body_, {final_velocity_x, final_velocity_y});
}

void Character::AddVelocity(std::optional<float> velocity_x, std::optional<float> velocity_y, float max_velocity_x, float max_velocity_y) {
    float current_velocity_x = b2Body_GetLinearVelocity(body_).x;
    float current_velocity_y = b2Body_GetLinearVelocity(body_).y;
    std::optional<float> final_velocity_x;
    std::optional<float> final_velocity_y;
    if (velocity_x) {
        final_velocity_x = current_velocity_x + velocity_x.value();
        if (final_velocity_x > max_velocity_x) {
            final_velocity_x = max_velocity_x;
        }
    }
    else {
        final_velocity_x = std::nullopt;
    }

    if (velocity_y) {
        final_velocity_y = current_velocity_y + velocity_y.value();
        if (final_velocity_y > max_velocity_y) {
            final_velocity_y = max_velocity_y;
        }
    }
    else {
        final_velocity_y = std::nullopt;
    }

    SetVelocity(final_velocity_x, final_velocity_y);

}

void Character::SubstractVelocity(std::optional<float> velocity_x, std::optional<float> velocity_y, float max_velocity_x, float max_velocity_y) {
    float current_velocity_x = b2Body_GetLinearVelocity(body_).x;
    float current_velocity_y = b2Body_GetLinearVelocity(body_).y;
    std::optional<float> final_velocity_x;
    std::optional<float> final_velocity_y;
    if (velocity_x) {
        final_velocity_x = current_velocity_x + velocity_x.value();
        if (final_velocity_x < max_velocity_x) {
            final_velocity_x = max_velocity_x;
        }
    }
    else {
        final_velocity_x = std::nullopt;
    }

    if (velocity_y) {
        final_velocity_y = current_velocity_y + velocity_y.value();
        if (final_velocity_y < max_velocity_y) {
            final_velocity_y = max_velocity_y;
        }
    }
    else {
        final_velocity_y = std::nullopt;
    }

    SetVelocity(final_velocity_x, final_velocity_y);

}



void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(visual_character_, states);
    // Debug
    if (Settings::debug_mode_) {
        target.draw(visual_rectangle_, states);
        target.draw(visual_top_circle_, states);
        //target.draw(visual_bottom_circle_, states);
        target.draw(visual_grounded_, states);
        target.draw(visual_head_, states);
        target.draw(visual_core_, states);
    }
}

void Character::SetGameIsRunningFalse() {
    game_is_running_ = false;
}

// Private
// Create the generals visuals shapes
void Character::SetupVisual() {
    visual_character_.setSize({width_, height_ + width_/2});
    visual_character_.setOrigin({width_/2, (height_ + width_)/2});
    visual_character_.setTexture(&texture_);
    // Debug
    // Rectangle
    visual_rectangle_.setSize({width_, height_});
    visual_rectangle_.setOrigin({width_/2, height_/2});
    visual_rectangle_.setFillColor(sf::Color(255, 255, 255, 126));

    // Circles
    visual_top_circle_.setRadius(width_/2);
    visual_top_circle_.setOrigin({width_/2, width_/2});
    visual_top_circle_.setFillColor(sf::Color(255, 255, 255, 126));

    // Sensor
    // grounded_
    visual_grounded_.setSize({(grounded_width_), (grounded_height_)});
    visual_grounded_.setOrigin({(grounded_width_/2), (grounded_height_/2)});
    visual_grounded_.setFillColor(sf::Color(255, 0, 0, 126));
    // head_
    visual_head_.setSize({(head_width_), (head_height_)});
    visual_head_.setOrigin({(head_width_/2), (head_height_/2)});
    visual_head_.setFillColor(sf::Color(255, 0, 0, 126));
    // core_
    visual_core_.setSize({(jump_detector_width_), (jump_detector_height_)});
    visual_core_.setOrigin({(jump_detector_width_/2), (jump_detector_height_/2)});
    visual_core_.setFillColor(sf::Color(255, 100, 255, 126));

//     visual_bottom_circle_.setRadius(width_/2);
//     visual_bottom_circle_.setOrigin({width_/2, width_/2});

}