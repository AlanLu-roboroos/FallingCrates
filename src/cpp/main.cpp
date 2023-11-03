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
  window.setFramerateLimit(256);

  if (!GameConstants::Textures::loadTextures()) {
    std::cout << "IMAGES NOT LOADED" << std::endl;
    return 1;
  }

  Background background;
  Crates crates;
  Grabber grabber(&crates);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Q) {
          window.close();
        } else if (event.key.code == sf::Keyboard::A) {
          if (!crates.spawnCrate(grabber.getColumn(), grabber.isActive())) {
            std::cout << "Full" << std::endl;
          }
        }
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          int line = std::abs(
              (event.mouseButton.x - (0.025987526 * window.getSize().x)) /
              (0.1185031185 * window.getSize().x));
          grabber.queueGoTo(line);
        }
      }
    }

    window.clear(GameConstants::BACKGROUND_COLOR);

    grabber.update();
    crates.update();

    background.drawBackground(window);
    grabber.drawGrabber(window);
    crates.drawCrates(window);

    window.display();
  }

  return 0;
}
