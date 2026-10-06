#pragma once

#include <SFML/Graphics.hpp>

struct Constants
{
    static constexpr float GRAVITY = 1000.f;  // m/s^2
    static constexpr float FRAME_RATE = 60.f; // frames per second
    static constexpr int SUB_STEPS = 4;
    static constexpr int MAX_PARTICLES = 20000;
    static constexpr int MAX_PARTICLE_SIZE = 1;
    static constexpr int MIN_PARTICLE_SIZE = 1;

    static constexpr int WINDOW_WIDTH = 1600;  // pixels
    static constexpr int WINDOW_HEIGHT = 1200; // pixels
    static constexpr sf::Vector2f BOX_SIZE = sf::Vector2f(WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50);
    static constexpr sf::Vector2f BOX_POS = sf::Vector2f((WINDOW_WIDTH - BOX_SIZE.x) / 2, (WINDOW_HEIGHT - BOX_SIZE.y) / 2);
    static constexpr sf::Time SPAWN_INTERVAL = sf::microseconds(10);
    
    static constexpr float CIRCLE_RADIUS = 250.0f;
    static constexpr sf::Vector2f CIRCLE_POS = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    static constexpr sf::Vector2f CANNON_POS = {CIRCLE_POS.x, CIRCLE_POS.y};

    static constexpr float COR = 0.1f; // coef of restitution
};
