#include <SFML/Graphics.hpp>

class Renderer
{
public:
    Renderer(sf::RenderWindow &window) : window_(window) {};
    void draw(std::vector<Particle> &particles)
    {
        for (const auto &particle : particles)
        {
            sf::CircleShape circle(particle.getRadius());
            circle.setPosition(particle.getPosition());
            sf::Color color(rand() % 255, rand() % 255, rand() % 255); // Random color
            circle.setFillColor(color); // Set the color of the particle
            window_.draw(circle);                // Draw the particle shape
        }
    };

    void drawBounds(std::pair<float, sf::Vector2f> bounds)
    {
        sf::CircleShape circle (bounds.first);
        circle.setPosition(bounds.second);
        circle.setFillColor(sf::Color::Black);
        window_.draw(circle);
    };

private:
    sf::RenderWindow &window_;
};