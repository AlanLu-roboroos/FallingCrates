#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
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

  static int CRATES_PER_LINE;
  static int CRATE_COLUMNS;

  static sf::Vector2f CRATE_SIZE;
  static sf::Vector2f SPAWN_SIZE;
  static sf::Vector2f PLATFORM_SIZE;
  static sf::Vector2f ITEM_SIZE;
  static sf::Vector2f ITEMS_BACKGROUND_SIZE;

  static sf::Vector2f GRABBER_START_POS;
  static float GRABBER_HORIZONTAL_SPEED;
  static float GRABBER_VERTICAL_SPEED;

  static float CRATE_GROWTH_TIME;
  static float CRATE_FADE_TIME;
  static float CRATE_FALLING_ACCELERATION;

  static float INFECT_TIME;

  static float BOMB_FLASHING_TIME;
  static float BOMB_EXPLODE_TIME;

  static int BORDER_HEIGHT;
  static int BORDER_WIDTH;

  static sf::Color BACKGROUND_COLOR;
  static sf::Color BORDER_COLOR;
  static sf::Color HEADER_COLOR;
  static sf::Color ITEM_BACKGROUND_COLOR;

  static int PLATFORM_HEIGHT;
  static int SPAWN_HEIGHT;
  static std::vector<int> COLUMN_X;
  static std::vector<int> ROW_Y;

  static std::vector<sf::Vector2f> PLATFORM_POS;
  static std::vector<sf::Vector2f> SPAWN_POS;
  static std::vector<sf::Vector2f> ITEMS_POS;

  enum CrateType {
    PURPLE_CRATE,
    BLUE_CRATE,
    GREEN_CRATE,
    YELLOW_CRATE,
    ORANGE_CRATE,
    RED_CRATE,
    PINK_CRATE,
    GOLD_CRATE,
    BOMB_CRATE,
    MEGA_BOMB_CRATE,
    HYPER_BOMB_CRATE,
    HEAVY_CRATE,
    UNBREAKABLE_CRATE,
    MULTICOLOR_CRATE,
    INFECTED_CRATE,
    NONE
  };

  static std::map<CrateType, int> CRATE_MERGE_SCORE;
  static std::map<CrateType, int> CRATE_EXPLODE_SCORE;

  class Resources {
  public:
    static sf::Texture PLATFORM_TEXTURE;
    static sf::Texture SPAWN_TEXTURE;

    static sf::Texture GRABBER_HORI;
    static sf::Texture GRABBER_LEFT;
    static sf::Texture GRABBER_RIGHT;
    static sf::Texture GRABBER_VERT;

    static sf::Texture CRATE_PURPLE_TEXTURE;
    static sf::Texture CRATE_BLUE_TEXTURE;
    static sf::Texture CRATE_GREEN_TEXTURE;
    static sf::Texture CRATE_YELLOW_TEXTURE;
    static sf::Texture CRATE_ORANGE_TEXTURE;
    static sf::Texture CRATE_RED_TEXTURE;
    static sf::Texture CRATE_PINK_TEXTURE;
    static sf::Texture CRATE_GOLD_TEXTURE;

    static sf::Texture CRATE_BOMB_TEXTURE;
    static sf::Texture CRATE_BOMB_FLASHING_TEXTURE;
    static sf::Texture CRATE_MEGA_BOMB_TEXTURE;
    static sf::Texture CRATE_MEGA_BOMB_FLASHING_TEXTURE;
    static sf::Texture CRATE_HYPER_BOMB_TEXTURE;
    static sf::Texture CRATE_HYPER_BOMB_FLASHING_TEXTURE;

    static sf::Texture CRATE_HEAVY_TEXTURE;
    static sf::Texture CRATE_UNBREAKABLE_TEXTURE;

    static sf::Texture CRATE_MULTICOLOR_TEXTURE;

    static sf::Texture CRATE_VIRUS_TEXTURE;

    static sf::Texture INFECTED_TEXTURE;

    static sf::Texture ITEM0_TEXTURE;
    static sf::Texture ITEM1_TEXTURE;
    static sf::Texture ITEM2_TEXTURE;

    static sf::Font SCORE_FONT;

    static bool loadResources(std::string path);
  };
};

#endif