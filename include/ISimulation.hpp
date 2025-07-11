#include <SFML/Graphics.hpp>

struct ISimulation
{
    virtual ~ISimulation() = default;
    virtual void handleEvent(const sf::Event &) = 0; // input
    virtual void update() = 0;                       // physics
    virtual void render(sf::RenderWindow &) = 0;     // draw
};