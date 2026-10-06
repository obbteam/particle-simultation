#include "../include/solver.hpp"
#include <iostream>
#include "math.h"
#include "../include/grid.hpp"

Solver::Solver(float timeStep, std::vector<Particle> &objects)
    : _time_step(timeStep), _objects(objects)
{
    objects.reserve(Constants::MAX_PARTICLES);
};


static void resolveParticles(Particle& p1, Particle &p2) {
    sf::Vector2f d = p1.getPosition() - p2.getPosition();

    float dist2 = d.x * d.x + d.y * d.y;
    float minDist = p1.getRadius() + p2.getRadius();

    if (dist2 >= minDist * minDist)
        return;

    float dist = std::sqrt(dist2);
    sf::Vector2f n = (dist > 1e-6f) ? d / dist : sf::Vector2f(1.f, 0.f);
    float delta = minDist - dist; // how much are they are jammed into each other
    
    float m1 = p1.getMass(), m2 = p2.getMass();
    float totalMass = m1 + m2;
    float massRatio = m1 / totalMass;

    sf::Vector2f v1 = p1.getPosition() - p1.getOldPosition();
    sf::Vector2f v2 = p2.getPosition() - p2.getOldPosition();

    p1.setPosition(p1.getPosition() + 0.5f * n * (1 - massRatio) * delta);
    p2.setPosition(p2.getPosition() - 0.5f * n * massRatio * delta);

    // impulse calculations
    sf::Vector2f relVel = v1 - v2;
    float accelAlongN = relVel.x * n.x + relVel.y * n.y;
    if (accelAlongN > 0.f)
        return; // already separating

    float j = -(1.f + Constants::COR) * accelAlongN / (1.f / m1 + 1.f / m2);

    sf::Vector2f impulse = j * n;

    p1.setOldPosition(p1.getOldPosition() - (impulse / m1));
    p2.setOldPosition(p2.getOldPosition() + (impulse / m2));
}


void Solver::applyCollisions()
{
    _grid.clear();

    for (int i = 0; i < _objects.size(); ++i) 
        _grid.insert(i, _objects[i].getPosition());

    for (int cy = 0; cy < _grid.rows; ++cy)
    {
        for (int cx = 0; cx < _grid.cols; ++cx)
        {
            auto &cell = _grid.cells[cy * _grid.cols + cx];
            if (cell.empty()) continue;

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int nx = cx + dx, ny = cy + dy;
                    if (nx < 0 || nx >= _grid.cols || ny < 0 || ny >=_grid.rows ) continue;

                    auto &other = _grid.cells[ny * _grid.cols + nx];
                    
                    for (int a: cell)
                        for (int b: other)
                            if (a < b)
                                resolveParticles(_objects[a], _objects[b]);
                }
            }
        }
    }
}




void Solver::pushObjects(sf::Clock &spawnClock)
{
    if (_objects.size() >= Constants::MAX_PARTICLES)
        return;

    /*--- spawn once every SPAWN_INTERVAL ---*/
    if (spawnClock.getElapsedTime() >= Constants::SPAWN_INTERVAL)

    {
        float vx = _cannon_amp * std::sin(_cannon_phase);
        _cannon_phase += _cannon_delta;

        /* create the particle ---------------------------------- */
        float radius = static_cast<float>(rand() % Constants::MAX_PARTICLE_SIZE + Constants::MIN_PARTICLE_SIZE);
        Particle p = Particle(radius,
                              {static_cast<uint8_t>(15),
                               static_cast<uint8_t>(94),
                               static_cast<uint8_t>(156)},
                              Constants::CANNON_POS, // start at the “cannon”
                              sf::Vector2f{vx, _cannon_y},
                              sf::Vector2f{0.f, 0.f}, // initial acceleration
                              _time_step);
        _objects.emplace_back(std::move(p));
        spawnClock.restart();
    }
}


void Solver::updateObjects(float dt)
{
    for (auto &particle : _objects)
    {
        particle.updatePosition(dt);
    }
}

void Solver::applyGravity()
{
    for (auto &particle : _objects)
    {
        particle.accelerate(_gravity);
    }
}

void Solver::changeGravity(const sf::Keyboard::Scancode &key)
{
    switch (key)
    {
    case sf::Keyboard::Scancode::Left:
        _gravity = {-Constants::GRAVITY, 0};
        break;
    case sf::Keyboard::Scancode::Up:
        _gravity = {0, -Constants::GRAVITY};
        break;
    case sf::Keyboard::Scancode::Right:
        _gravity = {Constants::GRAVITY, 0};
        break;
    case sf::Keyboard::Scancode::Down:
        _gravity = {0, Constants::GRAVITY};
        break;

    default:
        std::cerr << "Wrong Key for changeGravity" << std::endl;
    }
}
