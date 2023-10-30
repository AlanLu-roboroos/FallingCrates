#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(1920, 1200), "Falling Crates");
  window.setVerticalSyncEnabled(true);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Q) {
          window.close();
        }
      }
    }

    window.clear();
    window.display();
  }

  return 0;
}
