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
    std::cout << Constants::BOX_SIZE.x << Constants::BOX_SIZE.y << Constants::BOX_POS.x << Constants::BOX_POS.y << std::endl;

    for (int i = 0; i < 5; ++i)
    {
        Particle particle(10.0f, {100, 100}, {i, i}); // Create a particle with radius 10, position (100, 100), and velocity (0, 0)
        particles.emplace_back(particle);             // Create a particle with random position
    }

    auto [box_size, box_pos] = solver.getBoxBounds();

    std::cout << box_size.x << box_size.y << box_pos.x << box_pos.y << std::endl;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (
                sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
                sf::Mouse::getPosition(window).x > box_pos.x + 20 &&
                sf::Mouse::getPosition(window).x < box_size.x - 20 &&
                sf::Mouse::getPosition(window).y > box_pos.y + 20 &&
                sf::Mouse::getPosition(window).y < box_size.y - 20)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window is a sf::Window
                // left mouse button is pressed: create particle
                Particle particle(10.0f, {localPosition.x, localPosition.y}, {0, 0});
                particles.emplace_back(particle);
            }
        }

        window.clear(sf::Color::Black);
        renderer.drawBoxBounds(box_size, box_pos);

        solver.applyGravity(particles);     // Apply gravity to the particles
        solver.update(particles);           // Update the position of the particles
        solver.applyBoxBoundary(particles); // Check for collisions with the bounds
        renderer.draw(particles);           // Draw the particle shape
        window.display();
    }
}