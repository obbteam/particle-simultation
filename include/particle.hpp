#include <iostream>
#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle(float radius, sf::Vector2f position, sf::Vector2f velocity) : radius_(radius), position_(position), velocity_(velocity) {};

    float getRadius() const { return radius_; };
    sf::Vector2f getPosition() const { return position_; };
    sf::Vector2f getVelocity() const { return velocity_; };
    float dist(Particle &other)
    {
        auto o_pos = other.getPosition();
        return sqrtf((o_pos.x - position_.x) * (o_pos.x - position_.x) + (o_pos.y - position_.y) * (o_pos.y - position_.y));
    }
    void setPosition(const sf::Vector2f &position) { position_ = position; };
    void setVelocity(const sf::Vector2f &velocity) { velocity_ = velocity; };

private:
    float radius_;          // radius of the particle
    sf::Vector2f position_; // x, y
    sf::Vector2f velocity_; // x, y
};