#include "constants.hpp"

int GameConstants::WINDOW_WIDTH = 1924;
int GameConstants::WINDOW_HEIGHT = 1200;

sf::Vector2f GameConstants::CRATE_SIZE = sf::Vector2f(128, 128);

std::vector<sf::Vector2f> GameConstants::PLATFORM_POS = {
    sf::Vector2f(100, 990),
    sf::Vector2f(328, 990),
    sf::Vector2f(556, 990),
    sf::Vector2f(784, 990),
    sf::Vector2f(1012, 990),
    sf::Vector2f(1240, 990),
    sf::Vector2f(1468, 990),
    sf::Vector2f(1696, 990)};

std::string GameConstants::PLATFORM_TEXTURE_PATH = "src/res/objects/platform.png";
