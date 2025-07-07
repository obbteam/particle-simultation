#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/solver.hpp"
#include "include/renderer.hpp"

static sf::Clock spawnClock; // declared outside the loop

int main()
{
    sf::RenderWindow window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}), "Particle simulation!");
    window.setFramerateLimit(Constants::FRAME_RATE);
    Renderer renderer(window);
    std::vector<Particle> particles; // Vector to hold particles
    particles.reserve(1000);         // Reserve space for 1k particles

    Solver solver(1.f / Constants::FRAME_RATE, particles); // Create a solver with a time step of 1/60 seconds
    solver.setBoxBounds(Constants::BOX_SIZE, Constants::BOX_POS);

    auto [box_size, box_pos] = solver.getBoxBounds();

    while (window.isOpen())
    {
        auto start = std::chrono::high_resolution_clock::now();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i p = sf::Mouse::getPosition(window);

            if (p.x > box_pos.x + 20 && p.x < box_pos.x + box_size.x - 20 &&
                p.y > box_pos.y + 20 && p.y < box_pos.y + box_size.y - 20)
            {
                Particle par = Particle(10.f, {float(p.x), float(p.y)}, {0.f, 0.f});
                solver.pushParticle(par);
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
        renderer.drawBoxBounds(box_size, box_pos);
        renderer.updateNumberParticles(solver.getNumObjects());
        solver.pushParticles(spawnClock);
        solver.update();                    // Update the position of the particles
        renderer.draw(solver.getObjects()); // Draw the particle shape

        auto end = std::chrono::high_resolution_clock::now();

        const double dt = std::chrono::duration<double>(end - start).count();
        const double fps = 1.0 / dt; // dt already in seconds

        renderer.updateFPS(static_cast<float>(fps));

        window.display();
    }
}