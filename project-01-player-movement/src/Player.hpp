#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>

class Player {
private:
  float speed;
  sf::Texture texture;
  sf::Sprite body;

public:
  Player() {
    if (!texture.loadFromFile("assets/idle/idle-down.png")) {
      std::cout << "Failed to load the sprite.\n";
    }

    body.setTexture(texture);
    body.setPosition(0, 0);
    body.setScale(3.0f, 3.0f);
    speed = 200.0f;
  }

  sf::Vector2f normalizeDirection(sf::Vector2f direction) {
    float x = direction.x;
    float y = direction.y;
    float length = std::sqrt(x * x + y * y);

    if (length != 0) {
      direction.x /= length;
      direction.y /= length;
    }

    return direction;
  }

  void update(float deltaTime) {
    sf::Vector2f direction = {0.0f, 0.0f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      direction.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      direction.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      direction.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
      direction.x += 1;

    sf::Vector2f velocity = speed * deltaTime * normalizeDirection(direction);
    body.move(velocity);
  }

  void draw(sf::RenderWindow &window) { window.draw(body); }
};
