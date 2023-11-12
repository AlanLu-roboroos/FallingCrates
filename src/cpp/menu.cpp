#include "menu.hpp"

Menu::Button::Button(std::string _text, sf::Vector2f pos, sf::Vector2f size,
                     ButtonType _type) {
  text = sf::Text();
  text.setFont(GameConstants::Resources::SCORE_FONT);
  text.setFillColor(sf::Color(255, 255, 255));
  text.setCharacterSize(80);
  text.setString(_text);
  text.setOrigin(
      text.getLocalBounds().left + text.getLocalBounds().width / 2.0f,
      text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);
  text.setPosition(pos);

  border = sf::RectangleShape(size);
  border.setOrigin(
      border.getLocalBounds().left + border.getLocalBounds().width / 2.0f,
      border.getLocalBounds().top + border.getLocalBounds().height / 2.0f);
  border.setPosition(pos);
  border.setFillColor(sf::Color(50, 50, 50, 100));

  type = _type;
}

bool Menu::Button::update(sf::Vector2f mousePos, bool click) {
  if (border.getGlobalBounds().contains(mousePos)) {
    border.setFillColor(sf::Color(255, 255, 255));
    border.setFillColor(sf::Color(50, 50, 50, 200));
    if (click)
      return true;
  } else {
    border.setFillColor(sf::Color(255, 255, 255));
    border.setFillColor(sf::Color(50, 50, 50, 100));
  }
  return false;
}

void Menu::Button::drawButton(sf::RenderWindow &window) {
  window.draw(border);
  window.draw(text);
}

Menu::Menu() {
  m_state = MenuState::STARTING;
  startButtonList = {
      Button("START",
             sf::Vector2f(GameConstants::WINDOW_WIDTH / 2.0f,
                          GameConstants::WINDOW_HEIGHT / 2.0f - 140),
             sf::Vector2f(400, 100), ButtonType::START),
      Button("HELP",
             sf::Vector2f(GameConstants::WINDOW_WIDTH / 2.0f,
                          GameConstants::WINDOW_HEIGHT / 2.0f),
             sf::Vector2f(400, 100), ButtonType::HELP),
      Button("QUIT",
             sf::Vector2f(GameConstants::WINDOW_WIDTH / 2.0f,
                          GameConstants::WINDOW_HEIGHT / 2.0f + 140),
             sf::Vector2f(400, 100), ButtonType::QUIT)};
}

Menu::MenuState Menu::getState() { return m_state; }

void Menu::update(sf::Vector2f mousePos, bool click) {
  switch (m_state) {
  case MenuState::STARTING:
    for (auto &button : startButtonList) {
      if (button.update(mousePos, click)) {
        switch (button.type) {
        case ButtonType::START:
          m_state = MenuState::NONE;
          break;
        default:
          break;
        }
      }
    }
    break;
  case MenuState::PAUSING:
    break;
  case MenuState::HELPSCREEN:
    break;
  case MenuState::NONE:
    break;
  default:
    break;
  }
}

void Menu::displayMenu(sf::RenderWindow &window) {
  switch (m_state) {
  case MenuState::STARTING:
    backgroundRect.setSize(sf::Vector2f(600, 500));
    backgroundRect.setOrigin(backgroundRect.getLocalBounds().left +
                                 backgroundRect.getLocalBounds().width / 2.0f,
                             backgroundRect.getLocalBounds().top +
                                 backgroundRect.getLocalBounds().height / 2.0f);
    backgroundRect.setPosition(
        sf::Vector2f(GameConstants::WINDOW_WIDTH / 2.0f,
                     GameConstants::WINDOW_HEIGHT / 2.0f));
    backgroundRect.setFillColor(sf::Color(50, 50, 50, 150));
    window.draw(backgroundRect);
    for (auto button : startButtonList) {
      button.drawButton(window);
    }
    break;
  case MenuState::PAUSING:
    break;
  case MenuState::HELPSCREEN:
    break;
  case MenuState::NONE:
    break;
  default:
    break;
  }
}