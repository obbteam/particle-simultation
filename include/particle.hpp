#include <iostream>
#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle(float radius, sf::Vector2f position, sf::Vector2f velocity) : radius_(radius), position_(position), velocity_(velocity) {};

    float getRadius() const { return radius_; };
    sf::Vector2f getPosition() const { return position_; };
    sf::Vector2f getVelocity() const { return velocity_; };
    sf::Color getColor() const
    {
        return color_;
    }

    void setPosition(const sf::Vector2f &position) { position_ = position; };
    void setVelocity(const sf::Vector2f &velocity) { velocity_ = velocity; };

    void move(float dt)
    {
        position_ += velocity_ * dt;
    }

private:
    float radius_;          // radius of the particle
    sf::Vector2f position_; // x, y
    sf::Vector2f velocity_; // x, y
    sf::Color color_ = {rand() % 255, rand() % 255, rand() % 255};
};