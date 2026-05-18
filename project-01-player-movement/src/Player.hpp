#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

class Player {
private:
  float speed;
  sf::RectangleShape body;

public:
  Player() {
    body.setPosition(0, 0);
    body.setSize(sf::Vector2f(50.f, 50.f));
    body.setFillColor(sf::Color::White);
    speed = 200.0f;
  }

  void update(float deltaTime) {
    float velocity = speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      body.move(0, -velocity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      body.move(-velocity, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      body.move(0, velocity);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
      body.move(velocity, 0);
  }

  void draw(sf::RenderWindow &window) { window.draw(body); }
};
