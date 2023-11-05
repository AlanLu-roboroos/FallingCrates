#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"
#include "background.hpp"
#include "constants.hpp"
#include "crates.hpp"
#include "crates/purpleCrate.hpp"
#include "grabber.hpp"
#include "scorer.hpp"
#include <iostream>

int main() {
  sf::RenderWindow window(
      sf::VideoMode(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT),
      "Falling Crates");
  window.setFramerateLimit(360);

  if (!GameConstants::Resources::loadResources()) {
    std::cout << "IMAGES NOT LOADED" << std::endl;
    return 1;
  }

  Background background;
  Crates crates;
  Grabber grabber(&crates);
  Scorer scorer;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Q) {
          window.close();
        }
        // TEMPORARY CODE
        else if (event.key.code == sf::Keyboard::P) {
          if (!crates.spawnCrate(grabber.getColumn(), grabber.isActive())) {
            std::cout << "Full" << std::endl;
          }
        } else if (event.key.code == sf::Keyboard::B) {
          if (!crates.spawnCrate(grabber.getColumn(), grabber.isActive(),
                                 GameConstants::CrateType::BOMB_CRATE)) {
            std::cout << "Full" << std::endl;
          }
        } else if (event.key.code == sf::Keyboard::B) {
          if (!crates.spawnCrate(grabber.getColumn(), grabber.isActive(),
                                 GameConstants::CrateType::BOMB_CRATE)) {
            std::cout << "Full" << std::endl;
          }
        } else if (event.key.code == sf::Keyboard::A) {
          scorer.addScore(100, sf::Vector2f(164, 436));
        }
        // END TEMPORARY CODE
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
    scorer.drawScore(window);

    window.display();
  }

  return 0;
}
