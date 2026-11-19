//
// Created by zoade on 09.11.2026.
//

#include "../include/character.h"
// Public
// We enter the width and the height in pixels (for ease of use) and then convert it into meters
void Character::Setup(b2WorldId& world, b2Vec2 position, float width, float height){
    // Physics
    // variables setup
    width_ = width;
    height_ = height;

    // Sensor grounded_
    grounded_width_ = width_/1.1f;
    grounded_height_ = width_/2.0f;
    grounded_offset_y_ = height_/2; // (Problem, the sensor doesn't always work, i try to fix it via offset but it doesn't work)
    // Sensor head_
    head_width_ = width_/1.1f;
    head_height_ = width_/2.0f;
    head_offset_y_ = height_/2 + width_/2;
    // Sensor heart_
    heart_width_ = height_/2.0f;
    heart_height_ = height_/2.0f;
    heart_offset_y_ = width_/6;

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
    // heart_
    heart_.Setup(body_, heart_width_, (heart_height_), 0, heart_offset_y_, "heart_");
    SetupDebugVisual();
}

void Character::UpdateVisuals() {
    sf::Vector2f newPosition;
    newPosition.x = Conversion::Pixels(b2Body_GetPosition(body_).x);
    newPosition.y = 600 - Conversion::Pixels(b2Body_GetPosition(body_).y);
    // Debug Visual
    // Put the shapes togethers to form our visuals
    visual_rectangle_.setPosition(newPosition);
    visual_top_circle_.setPosition({newPosition.x, newPosition.y - height_/2});
    //visual_bottom_circle_.setPosition({newPosition.x, newPosition.y + height_/2});
    visual_grounded_.setPosition({newPosition.x, newPosition.y + grounded_offset_y_});
    visual_head_.setPosition({newPosition.x, newPosition.y - head_offset_y_});
    visual_heart_.setPosition({newPosition.x, newPosition.y - heart_offset_y_});

}

void Character::CharacterStates(double dt) {
    // Horizontal Movement (state, all frames)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
        if (b2Body_GetLinearVelocity(body_).x < 0.f) {
            SetVelocity(0,std::nullopt );
        }
        AddVelocity(speed_, std::nullopt, max_speed_, max_speed_);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
        if (b2Body_GetLinearVelocity(body_).x > 0.f) {
            SetVelocity(0,std::nullopt );
        }
        SubstractVelocity(-speed_, std::nullopt, -max_speed_, -max_speed_);
    } else {
        // by default the x velocity is at 0
        SetVelocity(0,std::nullopt );
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
    if (grounded_.HasTouched && b2Body_GetLinearVelocity(body_).y < 0.1f) {
        coyote_time_ = kCoyoteTimeMax_;
    }

    if (coyote_time_ > 0 && jump_buffer_ > 0) {
        // actual jump
        SetVelocity(std::nullopt, 22.5f);
        jump_buffer_ = 0;
        coyote_time_ = 0;
    }

    // Better Gravity
    float current_y_vel = b2Body_GetLinearVelocity(body_).y;

    if (current_y_vel < -0.1f) {
        // FALLING
        b2Body_SetGravityScale(body_, 2.5f);
    }
    else if (current_y_vel > 0.1f && !sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
        // CANCEL CURRENT JUMP
        b2Body_SetGravityScale(body_, 3.0f);
    }
    else {
        // ON GROUND, JUMPING
        b2Body_SetGravityScale(body_, 1.0f);
    }

    // update Sensor info
    if (grounded_.HasTouched) {
        visual_grounded_.setFillColor(sf::Color::Green);
    } else {
        visual_grounded_.setFillColor(sf::Color::Red);
    }
    if (head_.HasTouched) {
        visual_head_.setFillColor(sf::Color::Green);
    } else {
        visual_head_.setFillColor(sf::Color::Red);
    }
    if (heart_.HasTouched) {
        visual_heart_.setFillColor(sf::Color::Green);
    } else {
        visual_heart_.setFillColor(sf::Color::Red);
    }




}

void Character::CharacterEvents(std::optional<sf::Event> event){
    // Vertical Movement (event, once)
    // jump
    if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
        if (key->scancode == sf::Keyboard::Scancode::Space) {
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
    target.draw(visual_rectangle_, states);
    target.draw(visual_top_circle_, states);
    //target.draw(visual_bottom_circle_, states);
    target.draw(visual_grounded_, states);
    target.draw(visual_head_, states);
    target.draw(visual_heart_, states);
}

// Private
// Create the generals visuals shapes
void Character::SetupDebugVisual() {
    // Rectangle
    visual_rectangle_.setSize({width_, height_});
    visual_rectangle_.setOrigin({width_/2, height_/2});

    // Circles
    visual_top_circle_.setRadius(width_/2);
    visual_top_circle_.setOrigin({width_/2, width_/2});

    // Sensor
    // grounded_
    visual_grounded_.setSize({(grounded_width_), (grounded_height_)});
    visual_grounded_.setOrigin({(grounded_width_/2), (grounded_height_/2)});
    visual_grounded_.setFillColor(sf::Color::Red);
    // head_
    visual_head_.setSize({(head_width_), (head_height_)});
    visual_head_.setOrigin({(head_width_/2), (head_height_/2)});
    visual_head_.setFillColor(sf::Color::Red);
    // heart_
    visual_heart_.setSize({(heart_width_), (heart_height_)});
    visual_heart_.setOrigin({(heart_width_/2), (heart_height_/2)});
    visual_heart_.setFillColor(sf::Color::Red);

//     visual_bottom_circle_.setRadius(width_/2);
//     visual_bottom_circle_.setOrigin({width_/2, width_/2});

}