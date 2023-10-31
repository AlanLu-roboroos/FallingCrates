#include "constants.hpp"

int GameConstants::WINDOW_WIDTH = 1924;
int GameConstants::WINDOW_HEIGHT = 1500;

sf::Vector2f GameConstants::CRATE_SIZE = sf::Vector2f(128, 128);

std::vector<sf::Vector2f> GameConstants::PLATFORM_POS = {
    sf::Vector2f(100, 1289),
    sf::Vector2f(328, 1289),
    sf::Vector2f(556, 1289),
    sf::Vector2f(784, 1289),
    sf::Vector2f(1012, 1289),
    sf::Vector2f(1240, 1289),
    sf::Vector2f(1468, 1289),
    sf::Vector2f(1696, 1289)};

std::vector<sf::Vector2f> GameConstants::SPAWN_POS = {
    sf::Vector2f(100, 400),
    sf::Vector2f(328, 400),
    sf::Vector2f(556, 400),
    sf::Vector2f(784, 400),
    sf::Vector2f(1012, 400),
    sf::Vector2f(1240, 400),
    sf::Vector2f(1468, 400),
    sf::Vector2f(1696, 400)};

std::string GameConstants::PLATFORM_TEXTURE_PATH = "src/res/objects/platform.png";
std::string GameConstants::SPAWN_TEXTURE_PATH = "src/res/objects/spawn.png";
