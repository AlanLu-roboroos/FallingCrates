#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(1920, 1200), "Falling Crates");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.display();
  }

  return 0;
}
