#include "constants.hpp"

int GameConstants::WINDOW_WIDTH = 1924;
int GameConstants::WINDOW_HEIGHT = 1350;

int GameConstants::CRATES_PER_LINE = 6;
int GameConstants::CRATE_COLUMNS = 8;

sf::Vector2f GameConstants::CRATE_SIZE = sf::Vector2f(128, 128);
sf::Vector2f GameConstants::SPAWN_SIZE = sf::Vector2f(176, 176);
sf::Vector2f GameConstants::PLATFORM_SIZE = sf::Vector2f(176, 176);

sf::Vector2f GameConstants::GRABBER_START_POS = sf::Vector2f(962, 300);
float GameConstants::GRABBER_HORIZONTAL_SPEED = 8;
float GameConstants::GRABBER_VERTICAL_SPEED = 8;

float GameConstants::CRATE_GROWTH_TIME = 150;
float GameConstants::CRATE_FADE_TIME = 150;
float GameConstants::CRATE_FALLING_ACCELERATION = 0.0008;

float GameConstants::BOMB_FLASHING_TIME = 200;
float GameConstants::BOMB_EXPLODE_TIME = 10000;

int GameConstants::BORDER_HEIGHT = 146;
int GameConstants::BORDER_WIDTH = 10;

sf::Color GameConstants::BACKGROUND_COLOR = sf::Color(180, 180, 180);
sf::Color GameConstants::BORDER_COLOR = sf::Color(50, 50, 50);
sf::Color GameConstants::HEADER_COLOR = sf::Color(120, 120, 120);

int GameConstants::PLATFORM_HEIGHT = 1262;
int GameConstants::SPAWN_HEIGHT = 436;

std::vector<int> GameConstants::COLUMN_X = {164,  392,  620,  848,
                                            1076, 1304, 1532, 1760};
std::vector<int> GameConstants::ROW_Y = {1262, 1134, 1006, 878, 750, 622};

std::vector<sf::Vector2f> GameConstants::PLATFORM_POS = {
    sf::Vector2f(GameConstants::COLUMN_X[0], GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[1], GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[2], GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[3], GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[4], GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[5], GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[6], GameConstants::PLATFORM_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[7], GameConstants::PLATFORM_HEIGHT)};

std::vector<sf::Vector2f> GameConstants::SPAWN_POS = {
    sf::Vector2f(GameConstants::COLUMN_X[0], GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[1], GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[2], GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[3], GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[4], GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[5], GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[6], GameConstants::SPAWN_HEIGHT),
    sf::Vector2f(GameConstants::COLUMN_X[7], GameConstants::SPAWN_HEIGHT)};

std::map<GameConstants::CrateType, int> GameConstants::CRATE_MERGE_SCORE{
    {PURPLE_CRATE, 30},     {BLUE_CRATE, 90},       {GREEN_CRATE, 270},
    {YELLOW_CRATE, 810},    {ORANGE_CRATE, 2430},   {RED_CRATE, 7290},
    {PINK_CRATE, 21870},    {GOLD_CRATE, 65610},    {BOMB_CRATE, 90},
    {MEGA_BOMB_CRATE, 270}, {HYPER_BOMB_CRATE, 810}};

std::map<GameConstants::CrateType, int> GameConstants::CRATE_EXPLODE_SCORE{
    {PURPLE_CRATE, 30},     {BLUE_CRATE, 90},       {GREEN_CRATE, 270},
    {YELLOW_CRATE, 810},    {ORANGE_CRATE, 2430},   {RED_CRATE, 7290},
    {PINK_CRATE, 21870},    {GOLD_CRATE, 65610},    {BOMB_CRATE, 90},
    {MEGA_BOMB_CRATE, 270}, {HYPER_BOMB_CRATE, 810}};

sf::Texture GameConstants::Resources::PLATFORM_TEXTURE;
sf::Texture GameConstants::Resources::SPAWN_TEXTURE;
sf::Texture GameConstants::Resources::GRABBER_HORI;
sf::Texture GameConstants::Resources::GRABBER_LEFT;
sf::Texture GameConstants::Resources::GRABBER_RIGHT;
sf::Texture GameConstants::Resources::GRABBER_VERT;
sf::Texture GameConstants::Resources::CRATE_PURPLE_TEXTURE;
sf::Texture GameConstants::Resources::CRATE_BLUE_TEXTURE;
sf::Texture GameConstants::Resources::CRATE_GREEN_TEXTURE;
sf::Texture GameConstants::Resources::CRATE_YELLOW_TEXTURE;
sf::Texture GameConstants::Resources::CRATE_ORANGE_TEXTURE;
sf::Texture GameConstants::Resources::CRATE_RED_TEXTURE;
sf::Texture GameConstants::Resources::CRATE_PINK_TEXTURE;
sf::Texture GameConstants::Resources::CRATE_GOLD_TEXTURE;

sf::Texture GameConstants::Resources::CRATE_BOMB_TEXTURE;
sf::Texture GameConstants::Resources::CRATE_BOMB_FLASHING_TEXTURE;
sf::Texture GameConstants::Resources::CRATE_MEGA_BOMB_TEXTURE;
sf::Texture GameConstants::Resources::CRATE_MEGA_BOMB_FLASHING_TEXTURE;
sf::Texture GameConstants::Resources::CRATE_HYPER_BOMB_TEXTURE;
sf::Texture GameConstants::Resources::CRATE_HYPER_BOMB_FLASHING_TEXTURE;

sf::Texture GameConstants::Resources::CRATE_HEAVY_TEXTURE;
sf::Texture GameConstants::Resources::CRATE_UNBREAKABLE_TEXTURE;

sf::Texture GameConstants::Resources::CRATE_MULTICOLOR_TEXTURE;

sf::Font GameConstants::Resources::SCORE_FONT;

bool GameConstants::Resources::loadResources() {
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

  loaded &= CRATE_BOMB_TEXTURE.loadFromFile("src/res/crates/bomb.png");
  loaded &=
      CRATE_BOMB_FLASHING_TEXTURE.loadFromFile("src/res/crates/bomb-flash.png");
  loaded &= CRATE_MEGA_BOMB_TEXTURE.loadFromFile("src/res/crates/megabomb.png");
  loaded &= CRATE_MEGA_BOMB_FLASHING_TEXTURE.loadFromFile(
      "src/res/crates/megabomb-flash.png");
  loaded &=
      CRATE_HYPER_BOMB_TEXTURE.loadFromFile("src/res/crates/hyperbomb.png");
  loaded &= CRATE_HYPER_BOMB_FLASHING_TEXTURE.loadFromFile(
      "src/res/crates/hyperbomb-flash.png");

  loaded &= SCORE_FONT.loadFromFile("src/res/font.otf");

  return loaded;
}