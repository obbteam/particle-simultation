#pragma once

#include <SFML/Graphics.hpp>

struct ISimulation
{
    virtual ~ISimulation() = default;
    virtual void handleEvent(const std::optional<sf::Event> &) = 0; // input
    virtual void update() = 0;                                      // physics
    virtual void render() = 0;                                      // draw
};