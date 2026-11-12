//
// Created by zoade on 29.10.2026.
//

#include "../include/game.h"

// public
b2WorldDef def = b2DefaultWorldDef();
sf::Clock watch;
Character character;

void Game::BeginSetup() {
    // Window Setup
    window.create(sf::VideoMode({900, 600}), "Platformer", sf::Style::Default);
    window.setFramerateLimit(frame_rate_);
    // World setup
    def.gravity = {0.f, -9.81f};
    world_ = b2CreateWorld(&def);
    character.Setup(world_, {Conversion::Meters(900/2), Conversion::Meters(600/2)}, 50.f, 50.f);
}

void Game::Loop() {
    while (window.isOpen()) {
        const float dt = watch.restart().asSeconds(); // Delta Time, to make everything work, no matter the frame rate.
        // Windows related events
        WindowEvents();

        // World Step
        accumulator_ += dt;
        // make all steps similars (so it's reproducible), delta time dictates if there should be more or not
        while (accumulator_ >= kStep_) {
            b2World_Step(world_, kStep_, kSubStep_);
            accumulator_ -= kStep_;
        }

        character.UpdateVisuals();



        window.clear(sf::Color::Black);
        window.draw(character);
        window.display();
    }
}


// private
// This method may grow
void Game::WindowEvents() {
    while (const std::optional event = window.pollEvent()) {
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
    }
}



