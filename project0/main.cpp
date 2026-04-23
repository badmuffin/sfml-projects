#include <SFML/Graphics.hpp>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1000, 800), "Bouncing Ball");
    window.setFramerateLimit(60);

    sf::CircleShape ball(40.f);
    ball.setFillColor(sf::Color::Magenta);
    ball.setPosition(100.0f, 100.0f);

    sf::Vector2f velocity(1.5f, 0.8f);
    sf::Clock clock;

    float speed = 250.0f;

    while (window.isOpen())
    {
        float delta = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ball.move(velocity * delta * speed);

        sf::FloatRect ballBounds = ball.getGlobalBounds();
        sf::Vector2u winSize = window.getSize();

        if (ballBounds.left <= 0)
        {
            velocity.x = -velocity.x;
            // snap to left edge
            ball.setPosition(0, ball.getPosition().y);
        }
        else if (ballBounds.left + ballBounds.width >= winSize.x)
        {
            velocity.x = -velocity.x;
            // snap to right edge
            ball.setPosition(winSize.x - ballBounds.width, ball.getPosition().y);
        }

        if (ballBounds.top <= 0)
        {
            velocity.y = -velocity.y;
            // snap to top
            ball.setPosition(ball.getPosition().x, 0);
        }
        else if (ballBounds.top + ballBounds.height >= winSize.y)
        {
            velocity.y = -velocity.y;
            // snap to bottom
            ball.setPosition(ball.getPosition().x, winSize.y - ballBounds.height);
        }

        window.clear();
        window.draw(ball);
        window.display();
    }

    return 0;
}