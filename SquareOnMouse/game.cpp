//
// Created by zoade on 29.10.2026.
//

#include "game.h"
#include "square.h"

// public
Square square;
sf::Clock watch;

void Game::BeginWindow() {

    window.create(sf::VideoMode({900, 600}), "Square On Mouse", sf::Style::Default);
    window.setFramerateLimit(60);
}

void Game::Loop() {
    while (window.isOpen()) {
        const float dt = watch.restart().asSeconds();
        CheckEvents();

        // MOVE SQUARE
        square.SpawnSquareAtMouse(window);
        square.Fall(dt);

        window.clear(sf::Color::Black);
        // DRAW SQUARE
        square.Draw(window);
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



