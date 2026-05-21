#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <map>
#include <string>
#include <vector>

enum AnimationState {
  idleDown,
  idleLeft,
  idleRight,
  idleUp,
  runDown,
  runLeft,
  runRight,
  runUp
};

class Player {
private:
  float speed;

  sf::Sprite body;

  std::map<AnimationState, std::vector<sf::Texture>> animations;
  AnimationState currAnimState;
  int currFrame;

  float animationTimer;
  float frameDuration;

public:
  Player() {
    currAnimState = idleDown;
    currFrame = 0;
    animationTimer = 0.0f;
    frameDuration = 0.1f;

    loadAnimations();

    body.setTexture(animations[idleDown][0]);
    body.setPosition(0, 0);
    body.setScale(3.0f, 3.0f);
    speed = 200.0f;
  }

  void loadAnimations() {
    // load idle textures
    {
      sf::Texture texture;
      texture.loadFromFile("assets/idle/idle-down.png");
      animations[idleDown].push_back(texture);
    }
    {
      sf::Texture texture;
      texture.loadFromFile("assets/idle/idle-left.png");
      animations[idleLeft].push_back(texture);
    }
    {
      sf::Texture texture;
      texture.loadFromFile("assets/idle/idle-right.png");
      animations[idleRight].push_back(texture);
    }
    {
      sf::Texture texture;
      texture.loadFromFile("assets/idle/idle-up.png");
      animations[idleUp].push_back(texture);
    }

    // load other frames
    for (int i = 1; i <= 8; i++) {
      sf::Texture texture;
      texture.loadFromFile("assets/runDown/" + std::to_string(i) + ".png");
      animations[runDown].push_back(texture);
    }

    for (int i = 1; i <= 8; i++) {
      sf::Texture texture;
      texture.loadFromFile("assets/runLeft/" + std::to_string(i) + ".png");
      animations[runLeft].push_back(texture);
    }

    for (int i = 1; i <= 8; i++) {
      sf::Texture texture;
      texture.loadFromFile("assets/runRight/" + std::to_string(i) + ".png");
      animations[runRight].push_back(texture);
    }

    for (int i = 1; i <= 8; i++) {
      sf::Texture texture;
      texture.loadFromFile("assets/runUp/" + std::to_string(i) + ".png");
      animations[runUp].push_back(texture);
    }
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

  void updateAnimation(float deltaTime) {
    animationTimer += deltaTime;

    if (animationTimer >= frameDuration) {
      animationTimer = 0.0f;

      currFrame++;
      currFrame %= animations[currAnimState].size();

      body.setTexture(animations[currAnimState][currFrame]);
    }
  }

  void update(float deltaTime) {
    sf::Vector2f direction = {0.0f, 0.0f};
    bool isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      direction.y -= 1.0f;
      currAnimState = runUp;
      isMoving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      direction.x -= 1.0f;
      currAnimState = runLeft;
      isMoving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      direction.y += 1.0f;
      currAnimState = runDown;
      isMoving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      direction.x += 1.0f;
      currAnimState = runRight;
      isMoving = true;
    }

    if (!isMoving) {
      if (currAnimState == runDown)
        currAnimState = idleDown;

      else if (currAnimState == runLeft)
        currAnimState = idleLeft;

      else if (currAnimState == runRight)
        currAnimState = idleRight;

      else if (currAnimState == runUp)
        currAnimState = idleUp;

      currFrame = 0;
      body.setTexture(animations[currAnimState][0]);
    } else {
      updateAnimation(deltaTime);
    }

    sf::Vector2f velocity = speed * deltaTime * normalizeDirection(direction);
    body.move(velocity);
  }

  void draw(sf::RenderWindow &window) { window.draw(body); }
};
