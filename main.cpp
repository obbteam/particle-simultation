#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/solver.hpp"
#include "include/renderer.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}), "Particle simulation!");
    window.setFramerateLimit(Constants::FRAME_RATE);
    Renderer renderer(window);
    std::vector<Particle> particles; // Vector to hold particles
    particles.reserve(100);          // Reserve space for 100 particles

    Solver solver(1.f / Constants::FRAME_RATE); // Create a solver with a time step of 1/60 seconds
    solver.setBounds(Constants::BOUNDARY_RADIUS, Constants::BOUNDARY_POS);

    for (int i = 0; i < 100; ++i)
    {
        Particle particle(10.0f, {Constants::BOUNDARY_POS}, {i, i}); // Create a particle with radius 10, position (100, 100), and velocity (0, 0)
        particles.emplace_back(particle);                           // Create a particle with random position
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::White);
        renderer.drawBounds(solver.getBounds()); // Draw the bounds

        solver.applyGravity(particles); // Apply gravity to the particles
        solver.update(particles);       // Update the position of the particles
        solver.checkBounds(particles);  // Check for collisions with the bounds
        renderer.draw(particles);       // Draw the particle shape
        window.display();
    }
}