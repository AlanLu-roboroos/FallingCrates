#ifndef MENU_H
#define MENU_H

#include "SFML/Graphics.hpp"
#include "constants.hpp"
#include <iostream>
#include <string>
#include <vector>

class Menu {
public:
  enum MenuState { STARTING, PAUSING, NONE, QUITTING };
  enum ButtonType { START, PAUSE, RESUME, RESTART, RESET, QUIT };

  struct Button {
    sf::RectangleShape border;
    sf::Text text;
    ButtonType type;

    Button(std::string _text, int fontSize, sf::Vector2f pos, sf::Vector2f size,
           ButtonType _type);
    bool update(sf::Vector2f mousePos, bool click);
    void drawButton(sf::RenderWindow &window);
  };

private:
  MenuState m_state;

  sf::RectangleShape backgroundRect;

  std::vector<Button> startButtonList;
  std::vector<Button> pauseButtonList;

  Button pauseButton = Button(
      "PAUSE", 50, sf::Vector2f(140, GameConstants::BORDER_HEIGHT / 2.0f),
      sf::Vector2f(200, 80), ButtonType::PAUSE);

public:
  Menu();
  MenuState getState();
  bool update(sf::Vector2f mousePos, bool click);
  void displayMenu(sf::RenderWindow &window);
};

#endif