#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Bouncing Ball");
    window.setFramerateLimit(60);

    sf::CircleShape ball(20.f);
    ball.setFillColor(sf::Color::Magenta);
    ball.setPosition(100.0f, 100.0f);

    sf::Vector2f velocity(1.5f, 0.8f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ball.move(velocity);

        sf::Vector2 pos = ball.getPosition();
        float ballDiameter = 2 * ball.getRadius();

        if (pos.x <= 0 || pos.x + ballDiameter >= 1000)
            velocity.x = -velocity.x;
        if (pos.y <= 0 || pos.y + ballDiameter >= 800)
            velocity.y = -velocity.y;

        window.clear();
        window.draw(ball);
        window.display();
    }

    return 0;
}