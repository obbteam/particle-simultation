#pragma once

#include "ISimulation.hpp"
#include <SFML/Graphics.hpp>
#include "renderer.hpp"
#include "particle.hpp"
#include "solver.hpp"
#include "constants.hpp"

class CircleSimulation : public ISimulation
{
public:
    CircleSimulation(sf::RenderWindow &win, std::vector<Particle> &particles, float radius, sf::Vector2f pos);

    void handleEvent(const std::optional<sf::Event> &event) override;

    void update() override;

    void render() override;

    void leftMouseClick(const sf::Vector2i &mousePos);

    void applyCircleBoundary();

private:
    bool clickedInTheCircle(const sf::Vector2i &mousePos);

    sf::RenderWindow &window_;
    Renderer renderer_;
    float time_step_;
    Solver solver_;
    mutable sf::Clock spawnClock_;

    float circle_radius_;
    sf::Vector2f circle_pos_;
};