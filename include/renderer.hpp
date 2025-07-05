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
            circle.setOrigin({particle.getRadius(), particle.getRadius()});
            circle.setPosition(particle.getPosition());
            circle.setFillColor(particle.getColor());
            circle.setOutlineThickness(1.f);
            circle.setOutlineColor(sf::Color::Black);
            window_.draw(circle); // Draw the particle shape
        }
    };

    void drawBoxBounds(sf::Vector2f size, sf::Vector2f pos)
    {
        sf::RectangleShape box(size);
        box.setPosition(pos);
        box.setFillColor(sf::Color(211, 211, 211));
        box.setOutlineThickness(2.f);
        box.setOutlineColor(sf::Color::Black);
        window_.draw(box);
    }

    // collisions for this are not implemented
    void drawCircleBounds(std::pair<float, sf::Vector2f> bounds)
    {
        sf::CircleShape circle(bounds.first);
        circle.setPosition(bounds.second);
        circle.setFillColor(sf::Color::Black);
        window_.draw(circle);
    }

    void updateNumberParticles(int n)
    {
        const sf::Font font("ARIAL.TTF");
        sf::Text text(font, std::to_string(n), 30);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::Red);
        text.setPosition({5.f, 5.f});
        window_.draw(text);
    }

private:
    sf::RenderWindow &window_;
};