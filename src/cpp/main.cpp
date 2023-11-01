#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"
#include "background.hpp"
#include "constants.hpp"
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
  background.init();

  Grabber grabber;
  grabber.init();

  PurpleCrate crate;
  crate.setPosition(164, 1236);

  std::shared_ptr<Crate> crate1;
  crate1 = crate.nextCrate();
  crate1->setPosition(164, 1108);

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
    grabber.drawGrabber(window);
    crate.drawCrate(window);
    crate1->drawCrate(window);
    grabber.update();
    window.display();
  }

  return 0;
}
