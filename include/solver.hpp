#pragma once

#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include "constants.hpp"

class Solver
{
public:
    // Constructor
    Solver(float timeStep, std::vector<Particle> &objects);

    void setBoxBounds(sf::Vector2f size, sf::Vector2f pos)
    {
        _box_size = size;
        _box_pos = pos;
    }

    void applyCollisions();

    void applyBoxBoundary();

    void updateObjects(float dt);

    // Method to apply gravity to the particles
    void applyGravity();

    // Methid to change the gravity direction on Arrows
    void changeGravity(const sf::Keyboard::Scancode &key);

    void pushParticle(Particle &p) { _objects.emplace_back(std::move(p)); }
    void pushObjects(sf::Clock &spawnClock);

    std::tuple<sf::Vector2f, sf::Vector2f> getBoxBounds() const { return {_box_size, _box_pos}; }

    std::vector<Particle> &getObjects() { return _objects; }

    int getNumObjects() const { return _objects.size(); }

private:
    float _time_step; // Time step for the simulation
    sf::Vector2f _box_size = {0.f, 0.f};
    sf::Vector2f _box_pos = {0.f, 0.f};

    std::vector<Particle> &_objects;

    sf::Vector2f _gravity = {0, Constants::GRAVITY};

    float _cannon_phase = 0.f;       // or use this if you prefer a counter
    const float _cannon_amp = 250.f; // vertical amplitude    (pixels / sec)
    const float _cannon_y = 50.f;    // base speed to the left
    const float _cannon_delta = 0.1f;
};