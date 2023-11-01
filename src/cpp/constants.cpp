#include "constants.hpp"

int GameConstants::WINDOW_WIDTH = 1924;
int GameConstants::WINDOW_HEIGHT = 1350;

int CRATES_PER_LINE = 6;
int CRATE_COLUMNS = 8;

sf::Vector2f GameConstants::CRATE_SIZE = sf::Vector2f(128, 128);
sf::Vector2f GameConstants::SPAWN_SIZE = sf::Vector2f(176, 176);
sf::Vector2f GameConstants::PLATFORM_SIZE = sf::Vector2f(176, 176);

sf::Vector2f GameConstants::GRABBER_START_POS = sf::Vector2f(962, 300);

int GameConstants::BORDER_HEIGHT = 146;
int GameConstants::BORDER_WIDTH = 10;

sf::Color GameConstants::BACKGROUND_COLOR = sf::Color(180, 180, 180);
sf::Color GameConstants::BORDER_COLOR = sf::Color(50, 50, 50);
sf::Color GameConstants::HEADER_COLOR = sf::Color(120, 120, 120);

int GameConstants::PLATFORM_HEIGHT = 1236;
int GameConstants::SPAWN_HEIGHT = 410;

std::vector<sf::Vector2f> GameConstants::PLATFORM_POS = {
    sf::Vector2f(164, GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(392, GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(620, GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(848, GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(1076, GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(1304, GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(1532, GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(1760, GameConstants::PLATFORM_HEIGHT)};

std::vector<sf::Vector2f> GameConstants::SPAWN_POS = {
    sf::Vector2f(164, GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(392, GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(620, GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(848, GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(1076, GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(1304, GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(1532, GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(1760, GameConstants::SPAWN_HEIGHT)};

sf::Texture GameConstants::Textures::PLATFORM_TEXTURE;
sf::Texture GameConstants::Textures::SPAWN_TEXTURE;
sf::Texture GameConstants::Textures::GRABBER_HORI;
sf::Texture GameConstants::Textures::GRABBER_LEFT;
sf::Texture GameConstants::Textures::GRABBER_RIGHT;
sf::Texture GameConstants::Textures::GRABBER_VERT;
sf::Texture GameConstants::Textures::CRATE_PURPLE_TEXTURE;
sf::Texture GameConstants::Textures::CRATE_BLUE_TEXTURE;
sf::Texture GameConstants::Textures::CRATE_GREEN_TEXTURE;
sf::Texture GameConstants::Textures::CRATE_YELLOW_TEXTURE;
sf::Texture GameConstants::Textures::CRATE_ORANGE_TEXTURE;
sf::Texture GameConstants::Textures::CRATE_RED_TEXTURE;
sf::Texture GameConstants::Textures::CRATE_PINK_TEXTURE;
sf::Texture GameConstants::Textures::CRATE_GOLD_TEXTURE;

bool GameConstants::Textures::loadTextures() {
  bool loaded = true;
  loaded &= PLATFORM_TEXTURE.loadFromFile("src/res/objects/platform.png");
  loaded &= SPAWN_TEXTURE.loadFromFile("src/res/objects/spawn.png");

  loaded &= GRABBER_HORI.loadFromFile("src/res/grabber/grabberHori.png");
  loaded &= GRABBER_LEFT.loadFromFile("src/res/grabber/grabberLeft.png");
  loaded &= GRABBER_RIGHT.loadFromFile("src/res/grabber/grabberRigh.png");
  loaded &= GRABBER_VERT.loadFromFile("src/res/grabber/grabberVert.png");

  loaded &= CRATE_PURPLE_TEXTURE.loadFromFile("src/res/crates/purple.png");
  loaded &= CRATE_BLUE_TEXTURE.loadFromFile("src/res/crates/blue.png");
  loaded &= CRATE_GREEN_TEXTURE.loadFromFile("src/res/crates/green.png");
  loaded &= CRATE_YELLOW_TEXTURE.loadFromFile("src/res/crates/yellow.png");
  loaded &= CRATE_ORANGE_TEXTURE.loadFromFile("src/res/crates/orange.png");
  loaded &= CRATE_RED_TEXTURE.loadFromFile("src/res/crates/red.png");
  loaded &= CRATE_PINK_TEXTURE.loadFromFile("src/res/crates/pink.png");
  loaded &= CRATE_GOLD_TEXTURE.loadFromFile("src/res/crates/gold.png");

  return loaded;
}