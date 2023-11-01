#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"
#include "background.hpp"
#include "constants.hpp"
#include "crates.hpp"
#include "crates/purpleCrate.hpp"
#include "grabber.hpp"
#include <iostream>

int main() {
  sf::RenderWindow window(
      sf::VideoMode(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT),
      "Falling Crates");
  window.setFramerateLimit(60);

  if (!GameConstants::Textures::loadTextures()) {
    std::cout << "IMAGES NOT LOADED" << std::endl;
    return 1;
  }

  Background background;
  Grabber grabber;
  Crates crates;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Q) {
          window.close();
        } else if (event.key.code == sf::Keyboard::A) {
          Crate *crate(new PurpleCrate());
          crates.placeCrate(0, crate);
        }
      }
    }

    window.clear(GameConstants::BACKGROUND_COLOR);
    background.drawBackground(window);
    grabber.drawGrabber(window);
    crates.drawCrates(window);
    crates.update();
    grabber.update();
    window.display();
  }

  return 0;
}
