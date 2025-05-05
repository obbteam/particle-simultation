#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({600, 600}), "SFML works!");
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(shape);
        window.display();
    }
}