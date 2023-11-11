#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"
#include "background.hpp"
#include "constants.hpp"
#include "crates.hpp"
#include "crates/purpleCrate.hpp"
#include "grabber.hpp"
#include "items.hpp"
#include "scorer.hpp"
#include "spawner.hpp"
#include <iostream>

int main(int argc, char **args) {
  sf::RenderWindow window(
      sf::VideoMode(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT),
      "Falling Crates");
  window.setFramerateLimit(360);

  if (!GameConstants::Resources::loadResources(args[0])) {
    std::cout << "IMAGES NOT LOADED" << std::endl;
    return 1;
  }

  Scorer scorer;
  Background background;
  Crates crates(&scorer);
  Grabber grabber(&crates);
  Spawner spawner;
  Items items(&crates, &grabber, &spawner);

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
          }
        } else if (event.key.code == sf::Keyboard::B) {
          if (!crates.spawnCrate(grabber.getColumn(), grabber.isActive(),
                                 GameConstants::CrateType::BOMB_CRATE)) {
          }
        } else if (event.key.code == sf::Keyboard::U) {
          if (!crates.spawnCrate(grabber.getColumn(), grabber.isActive(),
                                 GameConstants::CrateType::UNBREAKABLE_CRATE)) {
          }
        } else if (event.key.code == sf::Keyboard::H) {
          if (!crates.spawnCrate(grabber.getColumn(), grabber.isActive(),
                                 GameConstants::CrateType::HEAVY_CRATE)) {
          }
        } else if (event.key.code == sf::Keyboard::B) {
          if (!crates.spawnCrate(grabber.getColumn(), grabber.isActive(),
                                 GameConstants::CrateType::BOMB_CRATE)) {
          }
        } else if (event.key.code == sf::Keyboard::M) {
          if (!crates.spawnCrate(grabber.getColumn(), grabber.isActive(),
                                 GameConstants::CrateType::MULTICOLOR_CRATE)) {
          }
        } else if (event.key.code == sf::Keyboard::R) {
          crates.clear();
          crates.resetSeenCrates();
        }
        // END TEMPORARY CODE
      }
      try {
        if (event.type == sf::Event::MouseButtonPressed) {
          if (event.mouseButton.button == sf::Mouse::Left) {
            if (event.mouseButton.y > GameConstants::BORDER_HEIGHT &&
                !items.isSelected()) {
              int line = std::max(
                  std::min(std::abs((event.mouseButton.x -
                                     (0.025987526 * window.getSize().x)) /
                                    (0.1185031185 * window.getSize().x)),
                           7.0),
                  0.0);
              grabber.queueGoTo(line);
            }
            items.activate(event.mouseButton.x, event.mouseButton.y,
                           window.getSize().x);
          }
        }
        if (event.type == sf::Event::MouseMoved) {
          items.updateMousePos(
              sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
        }
      } catch (...) {
      }
    }

    window.clear(GameConstants::BACKGROUND_COLOR);

    GameConstants::CrateType crate = spawner.update(crates.getSeenCrates());
    if (crate != GameConstants::CrateType::NONE) {
      crates.spawnCrate(grabber.getColumn(), grabber.isActive(), crate);
    }
    grabber.update();
    crates.update();
    items.update();

    background.drawBackground(window);
    grabber.drawGrabber(window);
    crates.drawCrates(window);
    scorer.drawScore(window);
    items.drawItems(window);

    window.display();
  }

  return 0;
}
