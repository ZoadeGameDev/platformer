//
// Created by zoade on 29.10.2026.
//

#include "../include/game.h"

// public
b2WorldDef def = b2DefaultWorldDef();
sf::Clock watch;
Character character;
std::array<PlatformBlock, 500> platform_blocks;
PlatformBlock big_platform_block;

void Game::BeginSetup() {
    // Window Setup
    window.create(sf::VideoMode({900, 600}), "Platformer", sf::Style::Default);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(frame_rate_);
    // World setup
    def.gravity = {0.f, -9.81f}; // usually -9.81f for gravity
    world_ = b2CreateWorld(&def);
    // SETUP THE LEVEL
    character.Setup(world_, {Conversion::Meters(900/2), Conversion::Meters(600/2)}, 50.f, 50.f);

    // for (int i = 0; i < platform_blocks.size(); ++i) {
    //     platform_blocks[i].Setup(world_, {Conversion::Meters( i * 90), Conversion::Meters(0)}, 50.f);
    // }
    big_platform_block.Setup(world_, {Conversion::Meters(0), Conversion::Meters(-400)}, 1000.f);

}

void Game::Loop() {
    while (window.isOpen()) {
        const float dt = watch.restart().asSeconds(); // Delta Time, to make everything work, no matter the frame rate.
        // Windows related events
        GameEvents();
        // World Step
        accumulator_ += dt;
        // make all steps similars (so it's reproducible), delta time dictates if there should be more or not
        while (accumulator_ >= kStep_) {
            b2World_Step(world_, kStep_, kSubStep_);
            accumulator_ -= kStep_;
        }

        // UPDATE ALL VISUALS
        character.UpdateVisuals();
        big_platform_block.UpdateVisuals();
        // for (PlatformBlock& block : platform_blocks) {
        //     block.UpdateVisuals();
        // }



        // SHOW ALL VISUALS
        window.clear(sf::Color::Black);
        window.draw(character);
        window.draw(big_platform_block);
        for (PlatformBlock& block : platform_blocks) {
            window.draw(block);
        }
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

        // CHARACTER EVENTS
        character.Move(event);
    }
}



