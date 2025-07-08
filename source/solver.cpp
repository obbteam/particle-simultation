#include "../include/solver.hpp"
#include <iostream>
#include "math.h"

Solver::Solver(float timeStep, std::vector<Particle> &objects)
    : _time_step(timeStep), _objects(objects) {};

void Solver::applyCollisions()
{
    for (int i = 0; i < _objects.size(); ++i)
    {
        for (int k = i + 1; k < _objects.size(); ++k)
        {
            auto &p1 = _objects[i];
            auto &p2 = _objects[k];

            sf::Vector2f n = p1.getPosition() - p2.getPosition();

            float dist = std::hypot(n.x, n.y);
            dist = dist == 0 ? 0.0001f : dist;
            auto minDist = p1.getRadius() + p2.getRadius();

            if (dist >= minDist)
                continue;

            float m1 = std::numbers::pi * p1.getRadius() * p1.getRadius();
            float m2 = std::numbers::pi * p2.getRadius() * p2.getRadius();

            // positional calculations
            n /= dist;                    // direction unit vector (length = 1)
            float delta = minDist - dist; // how much are they are jammed into each other
            float totalMass = m1 + m2;
            float massRatio = m1 / totalMass;

            p1.setPosition(p1.getPosition() + 0.5f * n * (1 - massRatio) * delta);
            p2.setPosition(p2.getPosition() - 0.5f * n * massRatio * delta);

            // impulse calculations
            auto v1 = p1.getPosition() - p1.getOldPosition();
            auto v2 = p2.getPosition() - p2.getOldPosition();
            sf::Vector2f relVel = v1 - v2;
            float accelAlongN = relVel.x * n.x + relVel.y * n.y;
            if (accelAlongN > 0.f)
                continue; // already separating

            float e = Constants::COR;
            float j = -(1.f + e) * accelAlongN / (1.f / m1 + 1.f / m2);

            sf::Vector2f impulse = j * n;

            p1.setOldPosition(p1.getOldPosition() - (impulse / m1));
            p2.setOldPosition(p2.getOldPosition() + (impulse / m2));
        }
    }
}

void Solver::pushParticles(sf::Clock &spawnClock)
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
                              {static_cast<uint8_t>(rand() % 255),
                               static_cast<uint8_t>(rand() % 255),
                               static_cast<uint8_t>(rand() % 255)},
                              Constants::CANNON_POS, // start at the “cannon”
                              sf::Vector2f{vx, _cannon_y},
                              sf::Vector2f{0.f, 0.f}, // initial acceleration
                              _time_step);
        _objects.emplace_back(std::move(p));
        spawnClock.restart();
    }
}

void Solver::applyCircleBoundary()
{
    for (auto &particle : _objects)
    {
        auto diff = particle.getPosition() - _circle_pos;
        auto dist = std::hypotf(diff.x, diff.y);

        float min_dist = _circle_radius - particle.getRadius();

        if (dist > min_dist && dist > 0.f)
        {
            auto n = diff / dist;
            particle.setPosition(_circle_pos + n * min_dist);
        }
    }
}

void Solver::applyBoxBoundary()
{
    auto left = _box_pos.x;
    auto right = _box_pos.x + _box_size.x;
    auto top = _box_pos.y;
    auto bottom = _box_pos.y + _box_size.y;
    for (auto &particle : _objects)
    {
        sf::Vector2f position = particle.getPosition();
        float radius = particle.getRadius();

        if (position.x - radius < left)
        {
            particle.setPosition({left + radius, position.y});
        }
        else if (position.x + radius > right)
        {
            particle.setPosition({right - radius, position.y});
        }

        if (position.y - radius < top)
        {
            particle.setPosition({position.x, top + radius});
        }
        else if (position.y + radius > bottom)
        {
            particle.setPosition({position.x, bottom - radius});
        }
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

void Solver::update()
{
    float substepT = _time_step / Constants::SUB_STEPS;
    for (int i = 0; i < Constants::SUB_STEPS; ++i)
    {
        applyGravity();
        applyCircleBoundary();
        applyCollisions();
        updateObjects(substepT);
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

void Solver::leftMouseClick(const sf::Vector2i mousePos)
{
    if (clickedInTheCircle(mousePos))
    {
        Particle par = Particle(Constants::MAX_PARTICLE_SIZE,
                                {static_cast<uint8_t>(rand() % 255),
                                 static_cast<uint8_t>(rand() % 255),
                                 static_cast<uint8_t>(rand() % 255)},
                                {float(mousePos.x), float(mousePos.y)},
                                {0.f, 0.f});
        pushParticle(par);
    }
}

bool Solver::clickedInTheCircle(const sf::Vector2i mousePos)
{
    auto diff = mousePos - sf::Vector2i(_circle_pos);
    auto dist = std::hypotf(diff.x, diff.y);
    if (dist > _circle_radius - Constants::MAX_PARTICLE_SIZE)
        return false;
    return true;
}