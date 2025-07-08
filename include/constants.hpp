#pragma once

#include <SFML/Graphics.hpp>

struct Constants
{
    static constexpr float GRAVITY = 1000.f;  // m/s^2
    static constexpr float FRAME_RATE = 60.f; // frames per second
    static constexpr int SUB_STEPS = 8;
    static constexpr int MAX_PARTICLES = 2000;
    static constexpr int MAX_PARTICLE_SIZE = 5;
    static constexpr int MIN_PARTICLE_SIZE = 1;

    static constexpr int WINDOW_WIDTH = 800;  // pixels
    static constexpr int WINDOW_HEIGHT = 600; // pixels
    static constexpr sf::Vector2f BOX_SIZE = sf::Vector2f(WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50);
    static constexpr sf::Vector2f BOX_POS = sf::Vector2f((WINDOW_WIDTH - BOX_SIZE.x) / 2, (WINDOW_HEIGHT - BOX_SIZE.y) / 2);
    static constexpr sf::Vector2f CANNON_POS = {BOX_POS.x + (BOX_SIZE.x / 2), BOX_POS.y + (BOX_SIZE.y / 4)};
    static constexpr sf::Time SPAWN_INTERVAL = sf::milliseconds(20);

    static constexpr float CIRCLE_RADIUS = 290.0f;
    static constexpr sf::Vector2f CIRCLE_POS = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

    static constexpr float COR = 0.7f; // coef of restitution
};
