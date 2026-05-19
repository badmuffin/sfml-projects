#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowStyle.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(1080, 800), "Top down player",
                          sf::Style::Default);
  sf::Clock clock;
  Player player;

  window.setFramerateLimit(60);

  while (window.isOpen()) {
    sf::Event event;
    float delta = clock.restart().asSeconds();

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    player.update(delta);

    window.clear();
    player.draw(window);
    window.display();
  }
}
