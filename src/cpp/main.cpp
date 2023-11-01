#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"
#include "background.hpp"
#include "constants.hpp"
#include "crates/crate.hpp"
#include "grabber.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT), "Falling Crates");
  window.setVerticalSyncEnabled(true);

  Background background;
  background.init();

  Grabber grabber;
  grabber.init();

  Crate crate(0, 0, 100);

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

    window.clear(sf::Color(180, 180, 180));
    background.drawBackground(window);
    crate.drawCrate(window);
    grabber.drawGrabber(window);
    grabber.update();
    window.display();
  }

  return 0;
}
