#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/solver.hpp"
#include "include/renderer.hpp"
#include "include/constants.hpp"
#include "include/ISimulation.hpp"
#include "include/circleSimulation.hpp"

static sf::Clock spawnClock; // declared outside the loop

int main()
{
    sf::RenderWindow window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}), "Particle simulation!");

    window.setFramerateLimit(Constants::FRAME_RATE);

    std::vector<Particle> p;

    std::unique_ptr<ISimulation> sim = std::make_unique<CircleSimulation>(window, p, Constants::CIRCLE_RADIUS, Constants::CIRCLE_POS);

    sf::Clock frameClock; // measures dt
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else
                sim->handleEvent(event);
        }
        float dt = frameClock.restart().asSeconds();

        sim->update();

        window.clear(sf::Color::Black);
        sim->render(window);

        float fps = 1.f / dt;
        Renderer::updateFPS(window, fps); // static helper
        window.display();
    }
}