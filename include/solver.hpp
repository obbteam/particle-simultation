#pragma once

#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include "constants.hpp"
#include "grid.hpp"

class Solver
{
public:
    // Constructor
    Solver(float timeStep, std::vector<Particle> &objects);

    void applyCollisions();

    void updateObjects(float dt);

    // Method to apply gravity to the particles
    void applyGravity();

    // Methid to change the gravity direction on Arrows
    void changeGravity(const sf::Keyboard::Scancode &key);

    void pushParticle(Particle &p) { _objects.emplace_back(std::move(p)); }
    void pushParticle(Particle &&p) { _objects.emplace_back(p); }
    void pushObjects(sf::Clock &spawnClock);

    std::vector<Particle> &getObjects() { return _objects; }

    int getNumObjects() const { return _objects.size(); }

private:
    float _time_step; // Time step for the simulation

    std::vector<Particle> &_objects;
    
    Grid _grid = {Grid(
        Constants::CIRCLE_POS.x - Constants::CIRCLE_RADIUS,
        Constants::CIRCLE_POS.y - Constants::CIRCLE_RADIUS,
        Constants::CIRCLE_RADIUS * 2,
        Constants::CIRCLE_RADIUS * 2,
        Constants::MAX_PARTICLE_SIZE * 2.f)};

    sf::Vector2f _gravity = {0, Constants::GRAVITY};

    float _cannon_phase = 0.f;       // or use this if you prefer a counter
    const float _cannon_amp = 250.f; // vertical amplitude    (pixels / sec)
    const float _cannon_y = 50.f;    // base speed to the left
    const float _cannon_delta = 0.1f;
};