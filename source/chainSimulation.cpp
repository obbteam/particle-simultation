#include "../include/chainSimulation.hpp"

ChainSimulation::ChainSimulation(sf::RenderWindow &win, std::vector<Particle> &particles)
    : window_(win),
      renderer_(win),
      time_step_(1.f / Constants::FRAME_RATE),
      solver_(time_step_, particles) {};

void ChainSimulation::update()
{
    float substepT = time_step_ / Constants::SUB_STEPS;
    for (int i = 0; i < Constants::SUB_STEPS; ++i)
    {
        // solver_.pushObjects(spawnClock_);
        // solver_.applyGravity();
        // applyCircleBoundary();
        // solver_.applyCollisions();
        // solver_.updateObjects(substepT);
    }
}

void ChainSimulation::render()
{
    renderer_.drawCircleBounds(Constants::CIRCLE_RADIUS, Constants::CIRCLE_POS);
    renderer_.updateNumberParticles(solver_.getNumObjects());
    renderer_.drawParticles(solver_.getObjects());
}