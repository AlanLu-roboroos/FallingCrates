#include "constants.hpp"

int GameConstants::WINDOW_WIDTH = 1924;
int GameConstants::WINDOW_HEIGHT = 1350;

sf::Vector2f GameConstants::CRATE_SIZE = sf::Vector2f(128, 128);
sf::Vector2f GameConstants::SPAWN_SIZE = sf::Vector2f(176, 176);

sf::Vector2f GameConstants::GRABBER_START_POS = sf::Vector2f(962, 300);

int GameConstants::BORDER_HEIGHT = 146;
int GameConstants::BORDER_WIDTH = 10;

sf::Color GameConstants::BORDER_COLOR = sf::Color(50, 50, 50);
sf::Color GameConstants::HEADER_COLOR = sf::Color(120, 120, 120);

std::vector<sf::Vector2f> GameConstants::PLATFORM_POS = {
    sf::Vector2f(164, 1189),  sf::Vector2f(392, 1189),
    sf::Vector2f(620, 1189),  sf::Vector2f(848, 1189),
    sf::Vector2f(1076, 1189), sf::Vector2f(1304, 1189),
    sf::Vector2f(1532, 1189), sf::Vector2f(1760, 1189)};

std::vector<sf::Vector2f> GameConstants::SPAWN_POS = {
    sf::Vector2f(164, 410),  sf::Vector2f(392, 410),  sf::Vector2f(620, 410),
    sf::Vector2f(848, 410),  sf::Vector2f(1076, 410), sf::Vector2f(1304, 410),
    sf::Vector2f(1532, 410), sf::Vector2f(1760, 410)};

sf::Texture GameConstants::Textures::PLATFORM_TEXTURE;
sf::Texture GameConstants::Textures::SPAWN_TEXTURE;
sf::Texture GameConstants::Textures::GRABBER_HORI;
sf::Texture GameConstants::Textures::GRABBER_LEFT;
sf::Texture GameConstants::Textures::GRABBER_RIGHT;
sf::Texture GameConstants::Textures::GRABBER_VERT;
sf::Texture GameConstants::Textures::CRATE_RED_TEXTURE;

bool GameConstants::Textures::loadTextures() {
  bool loaded = true;
  loaded &= PLATFORM_TEXTURE.loadFromFile("src/res/objects/platform.png");
  loaded &= SPAWN_TEXTURE.loadFromFile("src/res/objects/spawn.png");

  loaded &= GRABBER_HORI.loadFromFile("src/res/grabber/grabberHori.png");
  loaded &= GRABBER_LEFT.loadFromFile("src/res/grabber/grabberLeft.png");
  loaded &= GRABBER_RIGHT.loadFromFile("src/res/grabber/grabberRigh.png");
  loaded &= GRABBER_VERT.loadFromFile("src/res/grabber/grabberVert.png");

  loaded &= CRATE_RED_TEXTURE.loadFromFile("src/res/crates/red.png");

  return loaded;
}