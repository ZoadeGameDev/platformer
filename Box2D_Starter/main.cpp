//
// Created by zoade on 04.11.2026.
//
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include <print>


#include "game.h"

int main() {
    Game game;
    game.BeginSetup();
    game.Loop();
    return 0;
}