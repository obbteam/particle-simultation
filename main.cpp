#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/solver.hpp"
#include "include/renderer.hpp"
#include "include/constants.hpp"

static sf::Clock spawnClock; // declared outside the loop

int main()
{
    sf::RenderWindow window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}), "Particle simulation!");
    window.setFramerateLimit(Constants::FRAME_RATE);
    Renderer renderer(window);
    std::vector<Particle> particles; // Vector to hold particles
    particles.reserve(Constants::MAX_PARTICLES);          // Reserve space for 1k particles

    Solver solver(1.f / Constants::FRAME_RATE, particles); // Create a solver with a time step of 1/60 seconds

    solver.setCircleBounds(Constants::CIRCLE_RADIUS, Constants::CIRCLE_POS);

    while (window.isOpen())
    {
        auto start = std::chrono::high_resolution_clock::now();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (event->is<sf::Event::MouseButtonReleased>() &&
                     event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)
            {
                const auto *mb = event->getIf<sf::Event::MouseButtonReleased>();
                solver.leftMouseClick(mb->position);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            solver.changeGravity(sf::Keyboard::Scancode::Left);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            solver.changeGravity(sf::Keyboard::Scancode::Down);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            solver.changeGravity(sf::Keyboard::Scancode::Right);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            solver.changeGravity(sf::Keyboard::Scancode::Up);

        window.clear(sf::Color::Black);
        renderer.drawCircleBounds(Constants::CIRCLE_RADIUS, Constants::CIRCLE_POS);
        renderer.updateNumberParticles(solver.getNumObjects());
        solver.pushParticles(spawnClock);
        solver.update();                             // Update the position of the particles
        renderer.drawParticles(solver.getObjects()); // Draw the particle shape

        auto end = std::chrono::high_resolution_clock::now();

        const double dt = std::chrono::duration<double>(end - start).count();
        const double fps = 1.0 / dt; // dt already in seconds

        renderer.updateFPS(static_cast<float>(fps));

        window.display();
    }
}