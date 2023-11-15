#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"
#include "background.hpp"
#include "constants.hpp"
#include "crates.hpp"
#include "crates/purpleCrate.hpp"
#include "grabber.hpp"
#include "items.hpp"
#include "menu.hpp"
#include "scorer.hpp"
#include "spawner.hpp"
#include <iostream>

sf::Vector2f mouseToCoords(float x, float y, const sf::RenderWindow &window,
                           bool flipped = false) {
  if (flipped)
    return sf::Vector2f(x * (static_cast<float>(window.getSize().x) /
                             static_cast<float>(GameConstants::WINDOW_WIDTH)),
                        y * (static_cast<float>(window.getSize().y) /
                             static_cast<float>(GameConstants::WINDOW_HEIGHT)));
  else
    return sf::Vector2f(x * (static_cast<float>(GameConstants::WINDOW_WIDTH) /
                             static_cast<float>(window.getSize().x)),
                        y * (static_cast<float>(GameConstants::WINDOW_HEIGHT) /
                             static_cast<float>(window.getSize().y)));
}

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
  Menu menu;

  scorer.pause();
  crates.pause();
  grabber.pause();
  spawner.pause();
  items.pause();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Q) {
          window.close();
        } else if (event.key.code == sf::Keyboard::Num1)
          grabber.queueGoTo(0);
        else if (event.key.code == sf::Keyboard::Num2)
          grabber.queueGoTo(1);
        else if (event.key.code == sf::Keyboard::Num3)
          grabber.queueGoTo(2);
        else if (event.key.code == sf::Keyboard::Num4)
          grabber.queueGoTo(3);
        else if (event.key.code == sf::Keyboard::Num5)
          grabber.queueGoTo(4);
        else if (event.key.code == sf::Keyboard::Num6)
          grabber.queueGoTo(5);
        else if (event.key.code == sf::Keyboard::Num7)
          grabber.queueGoTo(6);
        else if (event.key.code == sf::Keyboard::Num8)
          grabber.queueGoTo(7);

        // TEMPORARY CODE
        if (argc == 2 && strcmp(args[1], "hi") == 0) {
          if (event.key.code == sf::Keyboard::P) {
            if (!crates.spawnCrate(grabber.getColumn(), grabber.isActive())) {
            }
          } else if (event.key.code == sf::Keyboard::B) {
            if (!crates.spawnCrate(grabber.getColumn(), grabber.isActive(),
                                   GameConstants::CrateType::BOMB_CRATE)) {
            }
          } else if (event.key.code == sf::Keyboard::U) {
            if (!crates.spawnCrate(
                    grabber.getColumn(), grabber.isActive(),
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
            if (!crates.spawnCrate(
                    grabber.getColumn(), grabber.isActive(),
                    GameConstants::CrateType::MULTICOLOR_CRATE)) {
            }
          } else if (event.key.code == sf::Keyboard::V) {
            if (!crates.spawnCrate(grabber.getColumn(), grabber.isActive(),
                                   GameConstants::CrateType::VIRUS_CRATE)) {
            }
          } else if (event.key.code == sf::Keyboard::I) {
            items.addItem();
          } else if (event.key.code == sf::Keyboard::R) {
            crates.clear();
            crates.resetSeenCrates();
          } else if (event.key.code == sf::Keyboard::Home) {
            scorer.pause();
            crates.pause();
            grabber.pause();
            spawner.pause();
            items.pause();
          } else if (event.key.code == sf::Keyboard::End) {
            scorer.play();
            crates.play();
            grabber.play();
            spawner.play();
            items.play();
          }
        }
        // END TEMPORARY CODE
      }
      try {
        if (event.type == sf::Event::MouseButtonPressed) {
          if (event.mouseButton.button == sf::Mouse::Left) {
            if (!menu.update(mouseToCoords(event.mouseButton.x,
                                           event.mouseButton.y, window, false),
                             true)) {
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
              sf::Vector2f temp = mouseToCoords(event.mouseButton.x,
                                                event.mouseButton.y, window);
              items.activate(event.mouseButton.x, temp.x, temp.y,
                             window.getSize().x);
            }
          }
        }
        if (event.type == sf::Event::MouseMoved) {
          items.updateMousePos(
              mouseToCoords(event.mouseMove.x, event.mouseMove.y, window));
          menu.update(mouseToCoords(event.mouseMove.x, event.mouseMove.y,
                                    window, false),
                      false);
        }
      } catch (...) {
      }
    }

    if (menu.getState() == Menu::MenuState::STARTING) {
      scorer.reset();
      crates.reset();
      grabber.reset();
      spawner.reset();
      items.reset();

    } else if (menu.getState() == Menu::MenuState::NONE) {
      scorer.play();
      crates.play();
      grabber.play();
      spawner.play();
      items.play();
    } else if (menu.getState() == Menu::MenuState::QUITTING) {
      window.close();
    } else {
      scorer.pause();
      crates.pause();
      grabber.pause();
      spawner.pause();
      items.pause();
    }

    window.clear(GameConstants::BACKGROUND_COLOR);

    GameConstants::CrateType crate = spawner.update(crates.getSeenCrates());
    if (crate != GameConstants::CrateType::NONE) {
      crates.spawnCrate(grabber.getColumn(), grabber.isActive(), crate);
    }
    grabber.update();
    crates.update();
    items.update();

    if (crates.getMergeCount() > 100) {
      items.addItem();
      crates.resetMergeCount();
    }

    background.drawBackground(window);
    grabber.drawGrabber(window);
    crates.drawCrates(window);
    scorer.drawScore(window);
    items.drawItems(window);
    menu.displayMenu(window);

    if (crates.isDead()) {
      menu.setDeathScreen();
      scorer.pause();
      crates.pause();
      grabber.pause();
      spawner.pause();
      items.pause();
    }

    window.display();
  }

  return 0;
}
