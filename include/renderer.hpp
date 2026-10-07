#pragma once
#include "constants.hpp"
#include "particle.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>

inline sf::Texture makeParticleTexture(unsigned size = 4)
{
    sf::Image img(sf::Vector2u{size, size}, sf::Color::Transparent);

    float center = (size - 1) / 2.f;
    float radius = size / 2.f;

    for (unsigned y = 0; y < size; ++y)
    {
        for (unsigned x = 0; x < size; ++x)
        {
            float dx = x - center;
            float dy = y - center;
            float d = std::sqrt(dx * dx + dy * dy) / radius;
            float a = std::clamp((1.f - d) * 6.f, 0.f, 1.f);

            img.setPixel({x, y}, sf::Color(255, 255, 255, static_cast<std::uint8_t>(a * 255.f)));
        }
    }

    sf::Texture tex;
    if (!tex.loadFromImage(img))
        throw std::runtime_error("particle texture failed");
    tex.setSmooth(true);
    return tex;
}

class Renderer
{
  public:
    Renderer(sf::RenderWindow& w)
        : window_(w), font_(), particlesNumText_(font_, "", 20),
          particleVertices_(sf::PrimitiveType::Triangles)
    {
        if (!font_.openFromFile("ARIAL.TTF"))
            throw std::runtime_error("font load failed");

        particlesNumText_.setStyle(sf::Text::Bold);
        particlesNumText_.setPosition({5.f, 5.f});
        particleTexture_ = makeParticleTexture(8);
    };

    void drawParticles(const std::vector<Particle>& particles)
    {
        const sf::Vector2f texSize(particleTexture_.getSize());

        particleVertices_.resize(particles.size() * 6);

        std::size_t i = 0;
        for (const auto& p : particles)
        {
            const sf::Vector2f pos = p.getPosition();
            const float r = p.getRadius() * Constants::VISUAL_SCALE;
            const sf::Color c = currentTheme().particle;

            const sf::Vector2f tl{pos.x - r, pos.y - r};
            const sf::Vector2f tr{pos.x + r, pos.y - r};
            const sf::Vector2f bl{pos.x - r, pos.y + r};
            const sf::Vector2f br{pos.x + r, pos.y + r};

            const sf::Vector2f uvTL{0.f, 0.f};
            const sf::Vector2f uvTR{texSize.x, 0.f};
            const sf::Vector2f uvBL{0.f, texSize.y};
            const sf::Vector2f uvBR{texSize.x, texSize.y};

            // two triangles per particle
            particleVertices_[i++] = {tl, c, uvTL};
            particleVertices_[i++] = {tr, c, uvTR};
            particleVertices_[i++] = {bl, c, uvBL};

            particleVertices_[i++] = {tr, c, uvTR};
            particleVertices_[i++] = {br, c, uvBR};
            particleVertices_[i++] = {bl, c, uvBL};
        }

        sf::RenderStates states;
        states.texture = &particleTexture_;
        window_.draw(particleVertices_, states);
    };

    void drawCircleBounds(float radius, sf::Vector2f pos)
    {
        sf::CircleShape circle(radius);
        circle.setOrigin({radius, radius});
        circle.setPosition(pos);
        circle.setFillColor(currentTheme().circle);
        circle.setOutlineThickness(2.f);
        circle.setOutlineColor(currentTheme().circleOutline);
        window_.draw(circle);
    }

    void updateNumberParticles(int n)
    {
        std::ostringstream oss;
        oss << n;
        particlesNumText_.setString(oss.str());
        particlesNumText_.setFillColor(currentTheme().countText);
        window_.draw(particlesNumText_);
    }

    static void updateFPS(sf::RenderWindow& window, float fps)
    {
        /* these locals are constructed once, the first time the
           function is called, and reused on every subsequent call */
        static sf::Font font;
        static bool ok = font.openFromFile("ARIAL.TTF"); // one-time I/O

        static sf::Text label(font, "", 20);
        if (ok)
        { // font loaded?
            label.setStyle(sf::Text::Bold);
            label.setFillColor(currentTheme().fpsText);
            label.setPosition({650.f, 5.f});
        }

        std::ostringstream oss;
        oss << "FPS: " << std::fixed << std::setprecision(1) << fps;
        label.setString(oss.str());
        window.draw(label);
    }

  private:
    sf::RenderWindow& window_;
    sf::Font font_;
    sf::VertexArray particleVertices_;
    sf::Text particlesNumText_;
    sf::Texture particleTexture_;
};