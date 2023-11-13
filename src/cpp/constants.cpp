#include "constants.hpp"

int GameConstants::WINDOW_WIDTH = 1924;
int GameConstants::WINDOW_HEIGHT = 1350;

int GameConstants::CRATES_PER_LINE = 6;
int GameConstants::CRATE_COLUMNS = 8;

sf::Vector2f GameConstants::CRATE_SIZE = sf::Vector2f(128, 128);
sf::Vector2f GameConstants::SPAWN_SIZE = sf::Vector2f(176, 176);
sf::Vector2f GameConstants::PLATFORM_SIZE = sf::Vector2f(176, 176);
sf::Vector2f GameConstants::ITEMS_BACKGROUND_SIZE = sf::Vector2f(100, 100);
sf::Vector2f GameConstants::ITEM_SIZE = sf::Vector2f(90, 90);

sf::Vector2f GameConstants::GRABBER_START_POS = sf::Vector2f(962, 300);
float GameConstants::GRABBER_HORIZONTAL_SPEED = 8;
float GameConstants::GRABBER_VERTICAL_SPEED = 8;

float GameConstants::CRATE_GROWTH_TIME = 150;
float GameConstants::CRATE_FADE_TIME = 150;
float GameConstants::CRATE_FALLING_ACCELERATION = 0.0008;

float GameConstants::INFECT_TIME = 5000;

float GameConstants::BOMB_FLASHING_TIME = 200;
float GameConstants::BOMB_EXPLODE_TIME = 5000;

int GameConstants::BORDER_HEIGHT = 146;
int GameConstants::BORDER_WIDTH = 10;

sf::Color GameConstants::BACKGROUND_COLOR = sf::Color(180, 180, 180);
sf::Color GameConstants::BORDER_COLOR = sf::Color(50, 50, 50);
sf::Color GameConstants::HEADER_COLOR = sf::Color(120, 120, 120);
sf::Color GameConstants::ITEM_BACKGROUND_COLOR = sf::Color(80, 80, 80);

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

std::vector<sf::Vector2f> GameConstants::ITEMS_POS = {
    sf::Vector2f(842, 80), sf::Vector2f(962, 80), sf::Vector2f(1082, 80)};

std::map<GameConstants::CrateType, int> GameConstants::CRATE_MERGE_SCORE{
    {PURPLE_CRATE, 30},     {BLUE_CRATE, 90},        {GREEN_CRATE, 270},
    {YELLOW_CRATE, 810},    {ORANGE_CRATE, 2430},    {RED_CRATE, 7290},
    {PINK_CRATE, 21870},    {GOLD_CRATE, 65610},     {BOMB_CRATE, 90},
    {MEGA_BOMB_CRATE, 270}, {HYPER_BOMB_CRATE, 810}, {MULTICOLOR_CRATE, 810}};

std::map<GameConstants::CrateType, int> GameConstants::CRATE_EXPLODE_SCORE{
    {PURPLE_CRATE, 5},     {BLUE_CRATE, 15},        {GREEN_CRATE, 45},
    {YELLOW_CRATE, 135},   {ORANGE_CRATE, 405},     {RED_CRATE, 1458},
    {PINK_CRATE, 3645},    {GOLD_CRATE, 10935},     {BOMB_CRATE, 15},
    {MEGA_BOMB_CRATE, 45}, {HYPER_BOMB_CRATE, 135}, {MULTICOLOR_CRATE, 135}};

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

sf::Texture GameConstants::Resources::CRATE_VIRUS_TEXTURE;

sf::Texture GameConstants::Resources::INFECTED_TEXTURE;

sf::Texture GameConstants::Resources::ITEM0_TEXTURE;
sf::Texture GameConstants::Resources::ITEM1_TEXTURE;
sf::Texture GameConstants::Resources::ITEM2_TEXTURE;

sf::Font GameConstants::Resources::SCORE_FONT;

bool GameConstants::Resources::loadResources(std::string path) {
  path = path.substr(0, path.size() - 4);
  bool loaded = true;
  loaded &= PLATFORM_TEXTURE.loadFromFile(path + "res/objects/platform.png");
  loaded &= SPAWN_TEXTURE.loadFromFile(path + "res/objects/spawn.png");

  loaded &= GRABBER_HORI.loadFromFile(path + "res/grabber/grabberHori.png");
  loaded &= GRABBER_LEFT.loadFromFile(path + "res/grabber/grabberLeft.png");
  loaded &= GRABBER_RIGHT.loadFromFile(path + "res/grabber/grabberRigh.png");
  loaded &= GRABBER_VERT.loadFromFile(path + "res/grabber/grabberVert.png");

  loaded &= CRATE_PURPLE_TEXTURE.loadFromFile(path + "res/crates/purple.png");
  loaded &= CRATE_BLUE_TEXTURE.loadFromFile(path + "res/crates/blue.png");
  loaded &= CRATE_GREEN_TEXTURE.loadFromFile(path + "res/crates/green.png");
  loaded &= CRATE_YELLOW_TEXTURE.loadFromFile(path + "res/crates/yellow.png");
  loaded &= CRATE_ORANGE_TEXTURE.loadFromFile(path + "res/crates/orange.png");
  loaded &= CRATE_RED_TEXTURE.loadFromFile(path + "res/crates/red.png");
  loaded &= CRATE_PINK_TEXTURE.loadFromFile(path + "res/crates/pink.png");
  loaded &= CRATE_GOLD_TEXTURE.loadFromFile(path + "res/crates/gold.png");

  loaded &= CRATE_BOMB_TEXTURE.loadFromFile(path + "res/crates/bomb.png");
  loaded &= CRATE_BOMB_FLASHING_TEXTURE.loadFromFile(
      path + "res/crates/bomb-flash.png");
  loaded &=
      CRATE_MEGA_BOMB_TEXTURE.loadFromFile(path + "res/crates/megabomb.png");
  loaded &= CRATE_MEGA_BOMB_FLASHING_TEXTURE.loadFromFile(
      path + "res/crates/megabomb-flash.png");
  loaded &=
      CRATE_HYPER_BOMB_TEXTURE.loadFromFile(path + "res/crates/hyperbomb.png");
  loaded &= CRATE_HYPER_BOMB_FLASHING_TEXTURE.loadFromFile(
      path + "res/crates/hyperbomb-flash.png");

  loaded &= CRATE_UNBREAKABLE_TEXTURE.loadFromFile(
      path + "res/crates/unbreakable.png");
  loaded &= CRATE_HEAVY_TEXTURE.loadFromFile(path + "res/crates/heavy.png");

  loaded &=
      CRATE_MULTICOLOR_TEXTURE.loadFromFile(path + "res/crates/multicolor.png");

  loaded &= CRATE_VIRUS_TEXTURE.loadFromFile(path + "res/crates/virus.png");

  loaded &= INFECTED_TEXTURE.loadFromFile(path + "res/crates/infected.png");

  loaded &= ITEM0_TEXTURE.loadFromFile(path + "res/items/item0.png");
  loaded &= ITEM1_TEXTURE.loadFromFile(path + "res/items/item1.png");
  loaded &= ITEM2_TEXTURE.loadFromFile(path + "res/items/item2.png");

  loaded &= SCORE_FONT.loadFromFile(path + "res/font.otf");

  return loaded;
}