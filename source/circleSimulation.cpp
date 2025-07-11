#include "../include/circleSimulation.hpp"
#include "math.h"

CircleSimulation::CircleSimulation(sf::RenderWindow &win, std::vector<Particle> &particles, float radius, sf::Vector2f pos)
    : window_(win),
      renderer_(win),
      time_step_(1.f / Constants::FRAME_RATE),
      solver_(time_step_, particles),
      circle_radius_(radius),
      circle_pos_(pos)
{
    particles.reserve(Constants::MAX_PARTICLES);
};

void CircleSimulation::handleEvent(const sf::Event &event)
{
    if (event.getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)
        leftMouseClick(event.getIf<sf::Event::MouseButtonReleased>()->position);

    solver_.changeGravity(event.getIf<sf::Event::KeyReleased>()->scancode);
}

void CircleSimulation::update()
{
    float substepT = time_step_ / Constants::SUB_STEPS;
    for (int i = 0; i < Constants::SUB_STEPS; ++i)
    {
        solver_.applyGravity();
        applyCircleBoundary();
        solver_.applyCollisions();
        solver_.updateObjects(substepT);
    }
}

void CircleSimulation::render(sf::RenderWindow &win)
{
    renderer_.drawCircleBounds(Constants::CIRCLE_RADIUS, Constants::CIRCLE_POS);
    renderer_.updateNumberParticles(solver_.getNumObjects());
    renderer_.drawParticles(solver_.getObjects());
}

void CircleSimulation::leftMouseClick(const sf::Vector2i &mousePos)
{
    if (clickedInTheCircle(mousePos))
    {
        Particle par = Particle(Constants::MAX_PARTICLE_SIZE,
                                {static_cast<uint8_t>(rand() % 255),
                                 static_cast<uint8_t>(rand() % 255),
                                 static_cast<uint8_t>(rand() % 255)},
                                {float(mousePos.x), float(mousePos.y)},
                                {0.f, 0.f});
        solver_.pushParticle(par);
    }
}

bool CircleSimulation::clickedInTheCircle(const sf::Vector2i &mousePos)
{
    auto diff = mousePos - sf::Vector2i(circle_pos_);
    auto dist = std::hypotf(diff.x, diff.y);
    if (dist > circle_radius_ - Constants::MAX_PARTICLE_SIZE)
        return false;
    return true;
}

void CircleSimulation::applyCircleBoundary()
{
    for (auto &particle : solver_.getObjects())
    {
        auto diff = particle.getPosition() - circle_pos_;
        auto dist = std::hypotf(diff.x, diff.y);

        float min_dist = circle_radius_ - particle.getRadius();

        if (dist > min_dist && dist > 0.f)
        {
            auto n = diff / dist;
            particle.setPosition(circle_pos_ + n * min_dist);
        }
    }
}
