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
    solver.setBoxBounds(Constants::BOX_SIZE, Constants::BOX_POS);

    // Particle particle1(10.0f, {25.0f, 750.0f}, {200.0f, 0.f});
    // Particle particle2(10.0f, {750.0f, 750.0f}, {-150.0f, 0.f});
    // particles.emplace_back(particle1);
    // particles.emplace_back(particle2);
    for (int i = 0; i < 10; ++i)
    {
        Particle particle(10.0f, {100.0f, 100.0f}, {i * 50.0f, i * 50.0f}); // Create a particle with radius 10, position (100, 100), and velocity (0, 0)
        particles.emplace_back(particle);                                   // Create a particle with random position
    }

    auto [box_size, box_pos] = solver.getBoxBounds();

    std::cout << box_pos.x << "<- x " << box_pos.y << "<-y" << std::endl;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (event->is<sf::Event::MouseButtonPressed>())
            {
                sf::Vector2i p = sf::Mouse::getPosition(window);

                if (p.x > box_pos.x + 20 && p.x < box_pos.x + box_size.x - 20 &&
                    p.y > box_pos.y + 20 && p.y < box_pos.y + box_size.y - 20)
                {
                    particles.emplace_back(Particle{10.f, {float(p.x), float(p.y)}, {0.f, 0.f}});
                }
            }
        }

        window.clear(sf::Color::Black);
        renderer.drawBoxBounds(box_size, box_pos);

        solver.applyGravity(particles);     // Apply gravity to the particles
        solver.update(particles);           // Update the position of the particles
        solver.applyBoxBoundary(particles); // Check for collisions with the bounds
        solver.applyCollisions(particles);
        renderer.draw(particles); // Draw the particle shape
        window.display();
    }
}