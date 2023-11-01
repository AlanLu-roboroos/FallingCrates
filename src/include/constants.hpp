#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <vector>

class GameConstants {
  // #define PLATFORM_POS std::vector<sf::Vector2f>({sf::Vector2f(50, 100),  \
//                                              sf::Vector2f(310, 100), \
//                                              sf::Vector2f(570, 100), \
//                                              sf::Vector2f(830, 100), \
//                                              sf::Vector2f(109, 100), \
//                                              sf::Vector2f(135, 100), \
//                                              sf::Vector2f(161, 100), \
//                                              sf::Vector2f(187, 100)})

  // #define WINDOW_WIDTH 1920
  // #define WINDOW_HEIGHT 1200

  // #define PLATFORM_TEXTURE_PATH std::string("res/objects/platform.png")
  public:
  static int WINDOW_WIDTH;
  static int WINDOW_HEIGHT;

  static sf::Vector2f CRATE_SIZE;
  static sf::Vector2f SPAWN_SIZE;

  static sf::Vector2f GRABBER_START_POS;

  static int BORDER_HEIGHT;
  static int BORDER_WIDTH;

  static sf::Color BORDER_COLOR;
  static sf::Color HEADER_COLOR;

  static std::vector<sf::Vector2f> PLATFORM_POS;
  static std::vector<sf::Vector2f> SPAWN_POS;

  static std::string PLATFORM_TEXTURE_PATH;
  static std::string SPAWN_TEXTURE_PATH;

  static std::string GRABBER_HORI_PATH;
  static std::string GRABBER_LEFT_PATH;
  static std::string GRABBER_RIGHT_PATH;
  static std::string GRABBER_VERT_PATH;
  static std::string CRATE_RED_TEXTURE_PATH;
};

#endif