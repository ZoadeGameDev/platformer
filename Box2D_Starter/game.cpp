//
// Created by zoade on 29.10.2026.
//

#include "game.h"

// public
sf::Clock watch;
b2WorldDef def = b2DefaultWorldDef();
Entity mario;
Entity platform;

void Game::BeginSetup() {

    window.create(sf::VideoMode({900, 600}), "Box2D test", sf::Style::Default);
    window.setFramerateLimit(60);
    monde_ = b2CreateWorld(&def);
    mario.Setup(sf::Color::Red, {450.f, 300.f}, {50.f, 50.f});
    mario.SetupPhysics(monde_, b2_dynamicBody, {20.f, 50.f});
    platform.Setup(sf::Color::Yellow, {450.f, 700.f}, {200.f, 50.f});
    platform.SetupPhysics(monde_, b2_staticBody, {20.f, 0.f});




}

void Game::Loop() {
    float accumulateur_ = 0.0f;
    constexpr float kPas = 1.f / 60.f;
    constexpr int kSousPas = 4;
    while (window.isOpen()) {

        const float dt = watch.restart().asSeconds();

        CheckEvents();

        def.gravity = {0.f, -9.81f}; // vers le bas en m/s^2
        accumulateur_ += dt;

        b2World_Step(monde_, kPas, kSousPas);
        std::println("Time accumulateur : {} + {}", accumulateur_, dt);
         while (accumulateur_ >= kPas)
         {
             b2World_Step(monde_, kPas, kSousPas);
             //std::println("{} , Physics frame !!!!", accumulateur_);
             accumulateur_ -= kPas;
         }

        //platform.Update();
        mario.Update();
        platform.Update();



        window.clear(sf::Color::Black);
        window.draw(mario);
        window.draw(platform);
        window.display();
    }
}


// private
// This method will grow
void Game::CheckEvents() {
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



