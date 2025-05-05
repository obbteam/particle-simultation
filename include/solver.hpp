#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include <math.h>

struct Constants
{
    static constexpr float GRAVITY = 1000.f;  // m/s^2
    static constexpr float FRAME_RATE = 60.f; // frames per second
    static constexpr int WINDOW_WIDTH = 800;  // pixels
    static constexpr int WINDOW_HEIGHT = 1000; // pixels
    static constexpr float BOUNDARY_RADIUS = std::min(WINDOW_HEIGHT, WINDOW_WIDTH) / 2 - 50.f;
    static constexpr sf::Vector2f BOUNDARY_POS = sf::Vector2f(WINDOW_WIDTH / 2 - BOUNDARY_RADIUS, WINDOW_HEIGHT / 2 - BOUNDARY_RADIUS);
};

class Solver
{
public:
    // Constructor
    Solver(float timeStep) : timeStep_(timeStep) {};

    void setBounds(float radius, sf::Vector2f center)
    {
        boundary_center_ = center;
        boundary_radius_ = radius;
    }

    void applyBoundary(std::vector<Particle> &particles)
    {
        for (auto &particle : particles)
        {
            sf::Vector2f position = particle.getPosition();
            sf::Vector2f velocity = particle.getVelocity();
            auto distVector = boundary_center_ - position;
            float dist = sqrt(distVector.x*distVector.x + distVector.y * distVector.y);

            if (dist > boundary_radius_ - particle.getRadius()) {
                 
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

    std::pair<float, sf::Vector2f> getBounds() const
    {
        return std::make_pair(boundary_radius_, sf::Vector2f(boundary_center_.x, boundary_center_.y));
    }

private:
    float timeStep_;                                // Time step for the simulation
    float boundary_radius_ = 250.0f;                // Bounds of the simulation area
    sf::Vector2f boundary_center_ = {420.f, 420.f}; // Center of the bounds
};