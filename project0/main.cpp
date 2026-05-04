#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>

struct Ball {
  sf::CircleShape shape;
  sf::Vector2f velocity;
  float radius;
};

int main() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(1000, 800), "Bouncing Balls",
                          sf::Style::Default);
  window.setFramerateLimit(60);

  std::vector<Ball> balls;
  sf::Clock clock;

  while (window.isOpen()) {
    float delta = clock.restart().asSeconds();
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        Ball newBall;
        newBall.radius = 20.0f;
        newBall.shape.setRadius(newBall.radius);
        newBall.shape.setFillColor(sf::Color::Magenta);

        newBall.shape.setOrigin(newBall.radius, newBall.radius);
        newBall.shape.setPosition(static_cast<float>(event.mouseButton.x),
                                  static_cast<float>(event.mouseButton.y));

        newBall.velocity = sf::Vector2f(200.0f, 200.0f);
        balls.push_back(newBall);
      }
    }

    for (size_t i = 0; i < balls.size(); i++) {
      balls[i].shape.move(balls[i].velocity * delta);

      // wall collisions
      sf::Vector2f pos = balls[i].shape.getPosition();
      float radi = balls[i].radius;

      if (pos.x - radi < 0) {
        balls[i].velocity.x *= -1;
        balls[i].shape.setPosition(radi, pos.y);
      }

      if (pos.x + radi > 1000) {
        balls[i].velocity.x *= -1;
        balls[i].shape.setPosition(1000 - radi, pos.y);
      }

      if (pos.y - radi < 0) {
        balls[i].velocity.y *= -1;
        balls[i].shape.setPosition(pos.x, radi);
      }

      if (pos.y + radi > 800) {
        balls[i].velocity.y *= -1;
        balls[i].shape.setPosition(pos.x, 800 - radi);
      }

      // ball to ball collisions
      for (size_t j = i + 1; j < balls.size(); j++) {
        sf::Vector2f posA = balls[i].shape.getPosition();
        sf::Vector2f posB = balls[j].shape.getPosition();

        sf::Vector2f diffAnB = posA - posB; // ans: d(x, y)

        // Pythagoras theorem: d^2 = (x2 - x1)^2 + (y2 - y1)^2
        float distBetweenBothPointsInSq =
            diffAnB.x * diffAnB.x + diffAnB.y * diffAnB.y;
        float radiusSum = balls[i].radius + balls[j].radius;

        if (distBetweenBothPointsInSq <= radiusSum * radiusSum) {
          balls[i].shape.setFillColor(sf::Color::Cyan);
          balls[j].shape.setFillColor(sf::Color::Cyan);
        }
      }
    }

    window.clear();
    for (auto &b : balls)
      window.draw(b.shape);
    window.display();
  }

  return 0;
}
