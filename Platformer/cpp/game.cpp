//
// Created by zoade on 29.10.2026.
//

#include "../include/game.h"

// public
b2WorldDef def = b2DefaultWorldDef();
sf::Clock watch;
DeathZone death_zone1;
DeathZone death_zone2;
DeathZone death_zone3;
DeathZone death_zone4;
DeathZone death_zone5;
Platform platform1;
Platform platform2;
Platform platform3;
Platform platform4;
JumpStar jump_star1;
JumpStar jump_star2;
JumpStar jump_star3;
PassPlatform pass_platform1;
PassPlatform pass_platform2;
PassPlatform pass_platform3;
PassPlatform pass_platform4;
Flag flag1;
Flag flag2;
WinZone win_zone;
Character character;

sf::Texture background_texture;
sf::RectangleShape background_shape;


void Game::BeginSetup() {
    // Window Setup
    window.create(sf::VideoMode({2000, 1200}), "Platformer", sf::Style::Default);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(frame_rate_);
    // World setup
    def.gravity = {0.f, -20.f}; // usually -9.81f for graif vity
    world_ = b2CreateWorld(&def);
    // SETUP FOR TRAVERSABLE PLATFORMS
    b2World_SetPreSolveCallback(world_, SolidContact, nullptr);
    // SETUP THE LEVEL
    // death window
    death_zone1.Setup(world_, {Conversion::Meters(0), Conversion::Meters(600)}, 100.f, 1300.f);
    death_zone2.Setup(world_, {Conversion::Meters(1000), Conversion::Meters(0)}, 2000.f, 100.f);
    death_zone3.Setup(world_, {Conversion::Meters(2000), Conversion::Meters(600)}, 100.f, 1300.f);
    death_zone4.Setup(world_, {Conversion::Meters(1000), Conversion::Meters(1200)}, 2000.f, 100.f);
    death_zone5.Setup(world_, {Conversion::Meters(750), Conversion::Meters(600)}, 1600.f, 50.f);
    // platforms
    platform1.Setup(world_, {Conversion::Meters(250), Conversion::Meters(125)}, 400.f, 150.f);
    platform2.Setup(world_, {Conversion::Meters(1600), Conversion::Meters(125)}, 700.f, 150.f);
    platform3.Setup(world_, {Conversion::Meters(850), Conversion::Meters(750)}, 200.f, 60.f);
    platform4.Setup(world_, {Conversion::Meters(250), Conversion::Meters(700)}, 400.f, 100.f);
    // jump stars
    jump_star1.Setup(world_, {Conversion::Meters(675), Conversion::Meters(230)}, 40.f, 40.f);
    jump_star2.Setup(world_, {Conversion::Meters(1025), Conversion::Meters(230)}, 40.f, 40.f);
    jump_star3.Setup(world_, {Conversion::Meters(1350), Conversion::Meters(855)}, 40.f, 40.f);
    // pass through platforms
    pass_platform1.Setup(world_, {Conversion::Meters(1800), Conversion::Meters(385)}, 250.f, 10.f);
    pass_platform2.Setup(world_, {Conversion::Meters(1800), Conversion::Meters(505)}, 250.f, 10.f);
    pass_platform3.Setup(world_, {Conversion::Meters(1800), Conversion::Meters(625)}, 250.f, 10.f);
    pass_platform4.Setup(world_, {Conversion::Meters(1800), Conversion::Meters(745)}, 250.f, 10.f);
    // flag
    flag1.Setup(world_, {Conversion::Meters(200), Conversion::Meters(250)}, 35.f, 35.f);
    flag2.Setup(world_, {Conversion::Meters(1875), Conversion::Meters(800)}, 35.f, 35.f);
    flag1.SetBool(true);
    // win zone
    win_zone.Setup(world_, {Conversion::Meters(150), Conversion::Meters(800)}, 35.f, 35.f);
    // character
    character.Setup(world_, {Conversion::Meters(325), Conversion::Meters(600/2)}, 50.f, 50.f);

    // Setup Background
    if (!background_texture.loadFromFile("../../Assets/Background.png")) {
        std::println("no texture");
    }
    background_shape.setSize({2000, 1200});
    background_shape.setOrigin({2000/2, (1200)/2});
    background_shape.setPosition({2000/2, (1200)/2});
    background_shape.setFillColor(sf::Color(255,255,255,225));
    background_shape.setTexture(&background_texture);
}

void Game::Loop() {
    while (window.isOpen()) {
        const double dt = watch.restart().asSeconds(); // Delta Time, to make everything work, no matter the frame rate.
        // Windows related events
        GameEvents();
        // World Step
        accumulator_ += dt;
        // make all steps similars (so it's reproducible), delta time dictates if there should be more or not
        while (accumulator_ >= kStep_) {
            b2World_Step(world_, kStep_, kSubStep_);
            SensorsContact(world_);
            accumulator_ -= kStep_;
        }

        character.CharacterStates(dt);

        // SENSOR EVENTS
        if (win_zone.CheckBool()) {
            character.SetGameIsRunningFalse();
        }
        if (flag2.CheckBool()) {
            character.ChangeCheckPointPosition(flag2.GetPositionX(), flag2.GetPositionY());
        }
        else if (flag1.CheckBool()) {
            character.ChangeCheckPointPosition(flag1.GetPositionX(), flag1.GetPositionY());
        }

        // UPDATE ALL VISUALS THAT NEEDS TO

        death_zone1.UpdateVisuals();
        death_zone2.UpdateVisuals();
        death_zone3.UpdateVisuals();
        death_zone4.UpdateVisuals();
        death_zone5.UpdateVisuals();
        platform1.UpdateVisuals();
        platform2.UpdateVisuals();
        platform3.UpdateVisuals();
        platform4.UpdateVisuals();
        jump_star1.UpdateVisuals();
        jump_star2.UpdateVisuals();
        jump_star3.UpdateVisuals();
        pass_platform1.UpdateVisuals();
        pass_platform2.UpdateVisuals();
        pass_platform3.UpdateVisuals();
        pass_platform4.UpdateVisuals();
        flag1.UpdateVisuals();
        flag2.UpdateVisuals();
        win_zone.UpdateVisuals();
        character.UpdateVisuals();
        // for (PlatformBlock& block : platform_blocks) {
        //     block.UpdateVisuals();
        // }


        // SHOW ALL VISUALS
        window.clear(sf::Color(255,255,255));
        window.draw(background_shape);
        window.draw(death_zone1);
        window.draw(death_zone2);
        window.draw(death_zone3);
        window.draw(death_zone4);
        window.draw(death_zone5);
        window.draw(platform1);
        window.draw(platform2);
        window.draw(platform3);
        window.draw(platform4);
        window.draw(jump_star1);
        window.draw(jump_star2);
        window.draw(jump_star3);
        window.draw(pass_platform1);
        window.draw(pass_platform2);
        window.draw(pass_platform3);
        window.draw(pass_platform4);
        window.draw(flag1);
        window.draw(flag2);
        window.draw(win_zone);
        window.draw(character);
        window.display();
    }
}


// private
// This method may grow
void Game::GameEvents() {
    while (const std::optional event = window.pollEvent()) {
        // WINDOW EVENTS
        // close window
        if (event -> is<sf::Event::Closed>()) {
            window.close();
        }

        // change window dimension
        if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            const sf::Vector2f taille(resized->size);
            window.setView(sf::View(sf::FloatRect({0.f, 0.f}, taille)));
        }

        // Debug Option

        if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->scancode == sf::Keyboard::Scancode::K) {
               Settings::debug_mode_ = !Settings::debug_mode_;
            }
        }
        if (const auto* button = event->getIf<sf::Event::JoystickButtonPressed>()) {
            if (button->button == 3) {
                Settings::debug_mode_ = !Settings::debug_mode_;
            }
        }

        // CHARACTER EVENTS
        character.CharacterEvents(event);
    }
}



