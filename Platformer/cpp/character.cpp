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

    grounded_width_ = width_/1.1f;
    grounded_height_ = width_/2.0f;
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
    grounded_.Setup(body_, grounded_width_, (grounded_height_), 0, -height_/2);
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
    visual_grounded_.setPosition({newPosition.x, newPosition.y + height_/2});
}

void Character::CharacterStates() {
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

    if (grounded_.HasTouched) {
        visual_grounded_.setFillColor(sf::Color::Green);
    } else {
        visual_grounded_.setFillColor(sf::Color::Red);
    }




}

void Character::CharacterEvents(std::optional<sf::Event> event){
    // Vertical Movement (event, once)
    // jump
    if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
        if (key->scancode == sf::Keyboard::Scancode::Space) {
            if (grounded_.HasTouched) {
                SetVelocity(std::nullopt, 22.5f);
            }
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

//     visual_bottom_circle_.setRadius(width_/2);
//     visual_bottom_circle_.setOrigin({width_/2, width_/2});

}