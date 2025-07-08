#include "../include/verlet.hpp"

VerletObject::VerletObject(const sf::Vector2f &initialPosition,
                           const sf::Vector2f &acceleration)
    : _old_position{initialPosition},
      _cur_position{initialPosition},
      _acceleration{acceleration} {}

void VerletObject::updatePosition(float dt)
{
    const sf::Vector2f Velocity = _cur_position - _old_position;
    _old_position = _cur_position;                                      // save the cur pos
    _cur_position = _cur_position + Velocity + _acceleration * dt * dt; // update the pos
    _acceleration = {};                                                 // reset the acceleration
};