#include <SFML/Graphics.hpp>

class Renderer
{
public:
    Renderer(sf::RenderWindow &w) : window_(w), font_(), fpsText_(font_, "", 20), particlesNumText_(font_, "", 20)
    {
        if (!font_.openFromFile("ARIAL.TTF"))
            throw std::runtime_error("font load failed");
        fpsText_.setStyle(sf::Text::Bold);
        fpsText_.setFillColor(sf::Color::Green);
        fpsText_.setPosition({650.f, 5.f});

        particlesNumText_.setStyle(sf::Text::Bold);
        particlesNumText_.setFillColor(sf::Color::Red);
        particlesNumText_.setPosition({5.f, 5.f});
    };

    void drawParticles(std::vector<Particle> &particles)
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

    void drawCircleBounds(float radius, sf::Vector2f pos)
    {
        sf::CircleShape circle(radius);
        circle.setOrigin({radius, radius});
        circle.setPosition(pos);
        circle.setFillColor(sf::Color(211, 211, 211));
        circle.setOutlineThickness(2.f);
        circle.setOutlineColor(sf::Color::Black);
        window_.draw(circle);
    }

    void updateNumberParticles(int n)
    {
        std::ostringstream oss;
        oss << n;
        particlesNumText_.setString(oss.str());
        window_.draw(particlesNumText_);
    }

    void updateFPS(float fps)
    {
        std::ostringstream oss;
        oss << "FPS: " << std::fixed << std::setprecision(1) << fps;
        fpsText_.setString(oss.str());
        window_.draw(fpsText_);
    }

private:
    sf::RenderWindow &window_;
    sf::Text fpsText_;
    sf::Text particlesNumText_;
    sf::Font font_;
};