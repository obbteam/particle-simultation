#pragma once

#include <SFML/Graphics.hpp>
#include "verlet.hpp"
#include "particle.hpp"
#include <math.h>

class Chain
{
public:
    Chain(Particle &obj1, Particle &obj2, float dist)
        : object1_(obj1),
          object2_(obj2),
          target_dist_(dist) {};

    void chainTogether()
    {
        auto axis = object1_.getPosition() - object2_.getPosition();
        float dist = std::hypotf(axis.x, axis.y);

        auto norm = axis / dist;
        float delta = target_dist_ - dist;

        object1_.setPosition(object1_.getPosition() + delta * norm * 0.5f);
        object2_.setPosition(object2_.getPosition() - delta * norm * 0.5f);
    };

private:
    Particle &object1_;
    Particle &object2_;

    float target_dist_;
};