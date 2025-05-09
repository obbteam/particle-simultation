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
            // sf::Color color(rand() % 255, rand() % 255, rand() % 255); // Random color
            sf::Color color = sf::Color::White;
            circle.setFillColor(color); // Set the color of the particle
            circle.setOutlineThickness(1.f);
            circle.setOutlineColor(sf::Color::Black);
            window_.draw(circle);                // Draw the particle shape
        }
    };

    void drawBoxBounds(sf::Vector2f size, sf::Vector2f pos) {
        sf::RectangleShape box (size);
        box.setPosition(pos);
        box.setFillColor(sf::Color::White);
        box.setOutlineThickness(2.f);
        box.setOutlineColor(sf::Color::Black);
        window_.draw(box);
    }


    // collisions for this are not implemented
    void drawCircleBounds(std::pair<float, sf::Vector2f> bounds)
    {
        sf::CircleShape circle (bounds.first);
        circle.setPosition(bounds.second);
        circle.setFillColor(sf::Color::Black);
        window_.draw(circle);
    };

private:
    sf::RenderWindow &window_;
};