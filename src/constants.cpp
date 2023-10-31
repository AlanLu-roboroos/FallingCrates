#include "constants.hpp"

int GameConstants::WINDOW_WIDTH = 1924;
int GameConstants::WINDOW_HEIGHT = 1350;

sf::Vector2f GameConstants::CRATE_SIZE = sf::Vector2f(128, 128);

std::vector<sf::Vector2f> GameConstants::PLATFORM_POS = {
    sf::Vector2f(100, 1139),
    sf::Vector2f(328, 1139),
    sf::Vector2f(556, 1139),
    sf::Vector2f(784, 1139),
    sf::Vector2f(1012, 1139),
    sf::Vector2f(1240, 1139),
    sf::Vector2f(1468, 1139),
    sf::Vector2f(1696, 1139)};

std::vector<sf::Vector2f> GameConstants::SPAWN_POS = {
    sf::Vector2f(100, 250),
    sf::Vector2f(328, 250),
    sf::Vector2f(556, 250),
    sf::Vector2f(784, 250),
    sf::Vector2f(1012, 250),
    sf::Vector2f(1240, 250),
    sf::Vector2f(1468, 250),
    sf::Vector2f(1696, 250)};

std::string GameConstants::PLATFORM_TEXTURE_PATH = "src/res/objects/platform.png";
std::string GameConstants::SPAWN_TEXTURE_PATH = "src/res/objects/spawn.png";
