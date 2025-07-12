#pragma once

#include "ISimulation.hpp"
#include <SFML/Graphics.hpp>
#include "renderer.hpp"
#include "particle.hpp"
#include "solver.hpp"
#include "constants.hpp"
#include "chain.hpp"

class ChainSimulation : public ISimulation
{
public:
    ChainSimulation(sf::RenderWindow &win, std::vector<Particle> &particles);

    void handleEvent(const std::optional<sf::Event> &event) override;

    void update() override;

    void render() override;

    void makeScene();

private:
    sf::RenderWindow &window_;
    Renderer renderer_;
    Solver solver_;

    std::vector<Chain> chains_;
    // std::vector<Particle> particles_;

    float time_step_ = 0.f;
};