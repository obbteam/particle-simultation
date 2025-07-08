#include <SFML/Graphics.hpp>
#include "verlet.hpp"

class Particle : public VerletObject
{
public:
    Particle(float radius, const sf::Vector2f initial_position, const sf::Vector2f acceleration)
        : radius_(radius), VerletObject(initial_position, acceleration) {};

    float getRadius() const { return radius_; };
    sf::Color getColor() const { return color_; };

private:
    float radius_; // radius of the particle
    sf::Color color_ = {rand() % 255, rand() % 255, rand() % 255};
};