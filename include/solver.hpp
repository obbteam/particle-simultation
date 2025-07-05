#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include <math.h>
#include <numbers>

struct Constants
{
    static constexpr float GRAVITY = 100.f;   // m/s^2
    static constexpr float FRAME_RATE = 60.f; // frames per second
    static constexpr int SUB_STEPS = 8;

    static constexpr int WINDOW_WIDTH = 800;  // pixels
    static constexpr int WINDOW_HEIGHT = 600; // pixels
    static constexpr sf::Vector2f BOX_SIZE = sf::Vector2f(WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50);
    static constexpr sf::Vector2f BOX_POS = sf::Vector2f((WINDOW_WIDTH - BOX_SIZE.x) / 2, (WINDOW_HEIGHT - BOX_SIZE.y) / 2);
    static constexpr sf::Vector2f CANNON_POS = {BOX_POS.x + (BOX_SIZE.x / 2), BOX_POS.y + (BOX_SIZE.y / 4)};
    static constexpr sf::Time SPAWN_INTERVAL = sf::milliseconds(60);

    static constexpr float COR = 0.7f; // coef of restitution
};

class Solver
{
public:
    // Constructor
    Solver(float timeStep, std::vector<Particle> objects) : timeStep_(timeStep), objects_(objects) {};

    void setBoxBounds(sf::Vector2f size, sf::Vector2f pos)
    {
        box_size_ = size;
        box_pos_ = pos;
    }

    void applyCollisions()
    {
        for (int i = 0; i < objects_.size(); ++i)
        {
            for (int k = i + 1; k < objects_.size(); ++k)
            {
                auto &p1 = objects_[i];
                auto &p2 = objects_[k];

                sf::Vector2f n = p1.getPosition() - p2.getPosition();

                float dist = std::hypot(n.x, n.y);
                dist = dist == 0 ? 0.0001f : dist;
                auto minDist = p1.getRadius() + p2.getRadius();

                if (dist >= minDist)
                    continue;

                float m1 = std::numbers::pi * p1.getRadius() * p1.getRadius();
                float m2 = std::numbers::pi * p2.getRadius() * p2.getRadius();

                // positional calculations
                n /= dist;                             // direction unit vector (length = 1)
                float delta = 0.5f * (minDist - dist); // how much are they are jammed into each other
                float totalMass = m1 + m2;
                float massRatio = m1 / totalMass;

                p1.setPosition(p1.getPosition() + n * (1 - massRatio) * delta);
                p2.setPosition(p2.getPosition() - n * massRatio * delta);

                // impulse calculations
                sf::Vector2f relVel = p1.getVelocity() - p2.getVelocity();
                float velAlongN = relVel.x * n.x + relVel.y * n.y;
                if (velAlongN > 0.f)
                    continue; // already separating

                float e = Constants::COR;
                float j = -(1.f + e) * velAlongN / (1.f / m1 + 1.f / m2);

                sf::Vector2f impulse = j * n;

                p1.setVelocity(p1.getVelocity() + impulse / m1);
                p2.setVelocity(p2.getVelocity() - impulse / m2);
            }
        }
    }

    void pushParticles(int n, sf::Clock &spawnClock)
    {
        if (objects_.size() >= 100)
            return;

        if (spawnClock.getElapsedTime() >= Constants::SPAWN_INTERVAL)
        {
            float x = std::sin(n);
            Particle p(rand() % 4 + 1, Constants::CANNON_POS, {x * 250.0f, 50.0f});
            objects_.push_back(p);
            spawnClock.restart();
        }
    }

    void applyBoxBoundary()
    {
        auto left = box_pos_.x;
        auto right = box_pos_.x + box_size_.x;
        auto top = box_pos_.y;
        auto bottom = box_pos_.y + box_size_.y;
        for (auto &particle : objects_)
        {
            sf::Vector2f position = particle.getPosition();
            sf::Vector2f velocity = particle.getVelocity();
            float radius = particle.getRadius();

            auto E = Constants::COR;

            if (position.x - radius < left)
            {
                particle.setPosition({left + radius, position.y});
                particle.setVelocity({E * velocity.x * -1, velocity.y});
            }
            else if (position.x + radius > right)
            {
                particle.setPosition({right - radius, position.y});
                particle.setVelocity({E * velocity.x * -1, velocity.y});
            }

            if (position.y - radius < top)
            {
                particle.setPosition({position.x, top + radius});
                particle.setVelocity({velocity.x, E * velocity.y * -1});
            }
            else if (position.y + radius > bottom)
            {
                particle.setPosition({position.x, bottom - radius});
                particle.setVelocity({velocity.x, E * velocity.y * -1});
            }
        }
    }

    void updateObjects(float substepT)
    {
        for (auto &particle : objects_)
        {
            particle.move(substepT);
        }
    }

    // Method to update the position of the particles
    void update()
    {
        float substepT = timeStep_ / Constants::SUB_STEPS;
        for (int i = 0; i < Constants::SUB_STEPS; ++i)
        {
            applyGravity();
            applyBoxBoundary();
            applyCollisions();
            updateObjects(substepT);
        }
    }

    // Method to apply gravity to the particles
    void applyGravity()
    {
        for (auto &particle : objects_)
        {
            sf::Vector2f newVelocity = particle.getVelocity() + sf::Vector2f(0, Constants::GRAVITY) * timeStep_;
            particle.setVelocity(newVelocity);
        }
    }

    std::tuple<sf::Vector2f, sf::Vector2f> getBoxBounds() const
    {
        return {box_size_, box_pos_};
    }

    std::vector<Particle> &getObjects()
    {
        return objects_;
    }

    void pushParticle(Particle &p)
    {
        objects_.emplace_back(p);
    }

private:
    float timeStep_; // Time step for the simulation
    sf::Vector2f box_size_ = {250.f, 250.f};
    sf::Vector2f box_pos_ = {0.f, 0.f};
    std::vector<Particle> objects_;
};