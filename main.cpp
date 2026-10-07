#include "include/ISimulation.hpp"
#include "include/circleSimulation.hpp"
#include "include/constants.hpp"
#include "include/renderer.hpp"
#include "include/solver.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <optional>

static sf::Clock spawnClock; // declared outside the loop

static int themeFromKey(sf::Keyboard::Key k)
{
    using K = sf::Keyboard::Key;
    if (k >= K::Num1 && k <= K::Num9)
        return static_cast<int>(k) - static_cast<int>(K::Num1);
    if (k >= K::Numpad1 && k <= K::Numpad9)
        return static_cast<int>(k) - static_cast<int>(K::Numpad1);
    return -1;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}),
                            "Particle simulation!");
    window.setFramerateLimit(Constants::FRAME_RATE);

    std::vector<Particle> p;
    std::unique_ptr<ISimulation> sim = std::make_unique<CircleSimulation>(
        window, p, Constants::CIRCLE_RADIUS, Constants::CIRCLE_POS);

    sf::Clock frameClock; // measures dt
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else
            {
                if (const auto* key = event->getIf<sf::Event::KeyPressed>())
                    selectTheme(themeFromKey(key->code)); // out-of-range values are ignored
                sim->handleEvent(event);
            }
        }
        float dt = frameClock.restart().asSeconds();

        sim->update();

        window.clear(currentTheme().background);
        window.setTitle(currentTheme().name);
        sim->render();

        float fps = 1.f / dt;
        Renderer::updateFPS(window, fps); // static helper
        window.display();
    }
}