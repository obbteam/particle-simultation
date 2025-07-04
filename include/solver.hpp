#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include <math.h>

struct Constants
{
    static constexpr float GRAVITY = 1000.f;   // m/s^2
    static constexpr float FRAME_RATE = 600.f; // frames per second
    static constexpr int WINDOW_WIDTH = 800;   // pixels
    static constexpr int WINDOW_HEIGHT = 600;  // pixels
    static constexpr sf::Vector2f BOX_SIZE = sf::Vector2f(WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50);
    static constexpr sf::Vector2f BOX_POS = sf::Vector2f((WINDOW_WIDTH - BOX_SIZE.x) / 2, (WINDOW_HEIGHT - BOX_SIZE.y) / 2);

    static constexpr float CIRCLE_RADIUS = std::min(WINDOW_HEIGHT, WINDOW_WIDTH) / 2 - 50.f;
    static constexpr sf::Vector2f CIRLCE_POS = sf::Vector2f(WINDOW_WIDTH / 2 - CIRCLE_RADIUS, WINDOW_HEIGHT / 2 - CIRCLE_RADIUS);
};

class Solver
{
public:
    // Constructor
    Solver(float timeStep) : timeStep_(timeStep) {};

    void setCircleBounds(float radius, sf::Vector2f center)
    {
        boundary_radius_ = radius;
        boundary_center_ = center;
    }

    void setBoxBounds(sf::Vector2f size, sf::Vector2f pos)
    {
        box_size_ = size;
        box_pos_ = pos;
    }

    void applyBoundary(std::vector<Particle> &particles)
    {
        for (auto &particle : particles)
        {
            sf::Vector2f position = particle.getPosition();
            sf::Vector2f velocity = particle.getVelocity();
            auto distVector = boundary_center_ - position;
            float dist = sqrt(distVector.x * distVector.x + distVector.y * distVector.y);

            if (dist > boundary_radius_ - particle.getRadius())
            {
            }
        }
    }

    void applyCollisions(std::vector<Particle> &particles)
    {
        for (int i = 0; i < particles.size(); ++i)
        {
            for (int j = i + 1; j < particles.size(); ++j)
            {
                sf::Vector2f v = particles[i].getPosition() - particles[j].getPosition();

                auto dist = sqrt(v.x * v.x + v.y * v.y);
                if (dist == 0.f)
                    dist = 0.0001f; // or random-jitter one of them
                auto minDist = particles[i].getRadius() + particles[j].getRadius();

                if (dist < minDist)
                {
                    auto u1 = particles[i].getVelocity();
                    auto u2 = particles[j].getVelocity();

                    auto m1 = particles[i].getRadius() * particles[i].getRadius();
                    auto m2 = particles[j].getRadius() * particles[j].getRadius();

                    std::cout << particles[i].getVelocity().x << ":" << particles[i].getVelocity().y << std::endl;
                    std::cout << particles[j].getVelocity().x << ":" << particles[j].getVelocity().y << std::endl;

                    sf::Vector2f norm = v / dist;          // direction unit vector (length = 1)
                    float delta = 0.5f * (minDist - dist); // how much are they are jammed into each other
                    float totalMass = m1 + m2;
                    float massRatio = m1 / totalMass;

                    particles[i].setPosition(particles[i].getPosition() + norm * (1 - massRatio) * delta);
                    particles[j].setPosition(particles[j].getPosition() - norm * massRatio * delta);

                    auto v1 = (m2 * (u2 - u1) + u1 * m1 + u2 * m2) / (m1 + m2);
                    auto v2 = (m1 * (u1 - u2) + u1 * m1 + u2 * m2) / (m1 + m2);
                    particles[i].setVelocity(v1);
                    particles[j].setVelocity(v2);

                    std::cout << particles[i].getVelocity().x << ":" << particles[i].getVelocity().y << std::endl;
                    std::cout << particles[j].getVelocity().x << ":" << particles[j].getVelocity().y << std::endl;
                }
            }
        }
    }

    void applyBoxBoundary(std::vector<Particle> &particles)
    {
        auto left = box_pos_.x;
        auto right = box_pos_.x + box_size_.x;
        auto top = box_pos_.y;
        auto bottom = box_pos_.y + box_size_.y;
        for (auto &particle : particles)
        {
            sf::Vector2f position = particle.getPosition();
            sf::Vector2f velocity = particle.getVelocity();
            float radius = particle.getRadius();

            if (position.x - radius < left)
            {
                particle.setPosition({left + radius, position.y});
                particle.setVelocity({velocity.x * -1, velocity.y});
            }
            else if (position.x + radius > right)
            {
                particle.setPosition({right - radius, position.y});
                particle.setVelocity({velocity.x * -1, velocity.y});
            }

            if (position.y - radius < top)
            {
                particle.setPosition({position.x, top + radius});
                particle.setVelocity({velocity.x, velocity.y * -1});
            }
            else if (position.y + radius > bottom)
            {
                particle.setPosition({position.x, bottom - radius});
                particle.setVelocity({velocity.x, velocity.y * -1});
            }
        }
    }

    // Method to update the position of the particles
    void update(std::vector<Particle> &particles)
    {
        for (auto &particle : particles)
        {
            sf::Vector2f newPosition = particle.getPosition() + particle.getVelocity() * timeStep_;
            particle.setPosition(newPosition);
        }
    }

    // Method to apply gravity to the particles
    void applyGravity(std::vector<Particle> &particles)
    {
        for (auto &particle : particles)
        {
            sf::Vector2f newVelocity = particle.getVelocity() + sf::Vector2f(0, Constants::GRAVITY) * timeStep_;
            particle.setVelocity(newVelocity);
        }
    }

    std::tuple<float, sf::Vector2f> getCircleBounds() const
    {
        return {boundary_radius_, sf::Vector2f(boundary_center_.x, boundary_center_.y)};
    }

    std::tuple<sf::Vector2f, sf::Vector2f> getBoxBounds() const
    {
        return {box_size_, box_pos_};
    }

private:
    float timeStep_; // Time step for the simulation
    sf::Vector2f box_size_ = {250.f, 250.f};
    sf::Vector2f box_pos_ = {0.f, 0.f};

    float boundary_radius_ = 250.0f;                // Bounds of the simulation area
    sf::Vector2f boundary_center_ = {420.f, 420.f}; // Center of the bounds
};