#pragma once

#include <SFML/Graphics.hpp>
#include <array>

struct Theme
{
    const char* name;
    sf::Color background;
    sf::Color circle;
    sf::Color circleOutline; // alpha 0 = no visible outline
    sf::Color particle;
    sf::Color fpsText;
    sf::Color countText;
};

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
    static constexpr sf::Vector2f BOX_POS =
        sf::Vector2f((WINDOW_WIDTH - BOX_SIZE.x) / 2, (WINDOW_HEIGHT - BOX_SIZE.y) / 2);
    static constexpr sf::Time SPAWN_INTERVAL = sf::microseconds(1);

    static constexpr float CIRCLE_RADIUS = 150.0f;
    static constexpr sf::Vector2f CIRCLE_POS = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    static constexpr sf::Vector2f CANNON_POS = {CIRCLE_POS.x, CIRCLE_POS.y};

    static constexpr float COR = 0.1f; // coef of restitution

    static constexpr float VISUAL_SCALE = 2.0f;

    static constexpr std::array<Theme, 5> THEMES = {{
        {"Ocean", sf::Color(16, 22, 36), sf::Color(255, 255, 255), sf::Color(0, 0, 0, 0),
         sf::Color(30, 136, 229), sf::Color(110, 231, 183), sf::Color(148, 163, 184)},
        {"Lava", sf::Color(26, 18, 32), sf::Color(255, 255, 255), sf::Color(0, 0, 0, 0),
         sf::Color(255, 107, 61), sf::Color(252, 211, 77), sf::Color(168, 160, 181)},
        {"Clean light", sf::Color(232, 236, 242), sf::Color(255, 255, 255),
         sf::Color(203, 213, 225), sf::Color(14, 165, 164), sf::Color(51, 65, 85),
         sf::Color(100, 116, 139)},
        {"Neon", sf::Color(12, 10, 24), sf::Color(24, 20, 48), sf::Color(0, 0, 0, 0),
         sf::Color(0, 229, 255), sf::Color(255, 64, 200), sf::Color(150, 140, 200)},
        {"Mint", sf::Color(17, 24, 39), sf::Color(240, 253, 250), sf::Color(0, 0, 0, 0),
         sf::Color(13, 148, 136), sf::Color(251, 191, 36), sf::Color(156, 163, 175)},
    }};
};

inline int g_themeIndex = 0;

inline const Theme& currentTheme()
{
    return Constants::THEMES[g_themeIndex];
}

inline void selectTheme(int index)
{
    if (index >= 0 && index < static_cast<int>(Constants::THEMES.size()))
        g_themeIndex = index;
}
