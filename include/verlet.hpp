#pragma once
#include <SFML/Graphics.hpp>

class VerletObject
{
public:
    // Constructor
    VerletObject(const sf::Vector2f &initialPosition,
                 const sf::Vector2f &acceleration);

    sf::Vector2f getOldPosition() const { return _old_position; }
    sf::Vector2f getPosition() const { return _cur_position; }
    sf::Vector2f getAcceleration() const { return _acceleration; }

    void updatePosition(float dt);
    void accelerate(const sf::Vector2f &acc) { _acceleration += acc; }
    void setOldPosition(const sf::Vector2f &pos) { _old_position = pos; }
    void setPosition(const sf::Vector2f &pos) { _cur_position = pos; }
    void setAcceleration(const sf::Vector2f &accel) { _acceleration = accel; }

private:
    sf::Vector2f _old_position;
    sf::Vector2f _cur_position;
    sf::Vector2f _acceleration;
};
