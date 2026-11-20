//
// Created by zoade on 29.10.2026.
//

#include "../include/game.h"

// public
b2WorldDef def = b2DefaultWorldDef();
sf::Clock watch;
Character character;
Platform big_platform;
PassPlatform small_platform;
JumpStar jump_star;
Flag flag_one;
DeathZone death_zone;

void Game::BeginSetup() {
    // Window Setup
    window.create(sf::VideoMode({900, 600}), "Platformer", sf::Style::Default);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(frame_rate_);
    // World setup
    def.gravity = {0.f, -20.f}; // usually -9.81f for gravity
    world_ = b2CreateWorld(&def);
    // SETUP FOR TRAVERSABLE PLATFORMS
    b2World_SetPreSolveCallback(world_, SolidContact, nullptr);
    // SETUP THE LEVEL
    character.Setup(world_, {Conversion::Meters(900/2), Conversion::Meters(600/2)}, 50.f, 50.f);
    big_platform.Setup(world_, {Conversion::Meters(900/2), Conversion::Meters(0)}, 600.f, 100.f);
    small_platform.Setup(world_, {Conversion::Meters(100), Conversion::Meters(200)}, 200.f, 25.f);
    jump_star.Setup(world_, {Conversion::Meters(700), Conversion::Meters(200)}, 25.f, 25.f);
    flag_one.Setup(world_, {Conversion::Meters(400), Conversion::Meters(200)}, 25.f, 25.f);
    death_zone.Setup(world_, {Conversion::Meters(900/2), Conversion::Meters(-25)}, 1000.f, 100.f);


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

        // UPDATE ALL VISUALS
        character.UpdateVisuals();
        big_platform.UpdateVisuals();
        small_platform.UpdateVisuals();
        jump_star.UpdateVisuals();
        flag_one.UpdateVisuals();
        death_zone.UpdateVisuals();
        // for (PlatformBlock& block : platform_blocks) {
        //     block.UpdateVisuals();
        // }


        // SHOW ALL VISUALS
        window.clear(sf::Color::Black);
        window.draw(death_zone);
        window.draw(big_platform);
        window.draw(small_platform);
        window.draw(jump_star);
        window.draw(flag_one);
        window.draw(character);
        window.display();
    }
}


// private
// This method may grow
void Game::GameEvents() {
    while (const std::optional event = window.pollEvent()) {
        // WINDOW EVENTS
        //CheckIfWindowClosed(event);
        // close window
        if (event -> is<sf::Event::Closed>()) {
            window.close();
        }

        // change window dimension
        if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            const sf::Vector2f taille(resized->size);
            window.setView(sf::View(sf::FloatRect({0.f, 0.f}, taille)));
        }

        // CHARACTER EVENTS AND CHECKPOINT CHECKS
        character.CharacterEvents(event);
        if (flag_one.CheckBool()) {
            character.ChangeCheckPointPosition(flag_one.GetPositionX(), flag_one.GetPositionY());
        }
    }
}



