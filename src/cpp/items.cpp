#include "items.hpp"

Items::Items(Crates *_crates) {
  m_items = {2, 2, 2};
  m_sprites.push_back(sf::Sprite(GameConstants::Resources::ITEM0_TEXTURE));
  m_sprites.push_back(sf::Sprite(GameConstants::Resources::ITEM1_TEXTURE));
  m_sprites.push_back(sf::Sprite(GameConstants::Resources::ITEM2_TEXTURE));
  for (int i = 0; i < m_sprites.size(); i++) {
    m_sprites[i].setOrigin(
        sf::Vector2f(m_sprites[i].getLocalBounds().width / 2,
                     m_sprites[i].getLocalBounds().height / 2));
    m_sprites[i].setScale(
        GameConstants::ITEM_SIZE.x / m_sprites[i].getLocalBounds().width,
        GameConstants::ITEM_SIZE.y / m_sprites[i].getLocalBounds().height);
    m_sprites[i].setPosition(GameConstants::ITEMS_POS[i]);
    m_sprites[i].setColor(sf::Color(255, 255, 255, 255));
  }
  m_itemTypeOrder = {COLUMN_FREEZE, TIME_SLOW, LINE_CLEAR};
  m_clocks = {Clock(), Clock(), Clock()};
  m_activated = {false, false, false};
  selected = ItemTypes::NONE;
  m_crates = _crates;

  m_timeFreezeBackdrop.setSize(
      sf::Vector2f(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT));
  m_timeFreezeBackdrop.setFillColor(sf::Color(0, 0, 100, 30));
}

void Items::drawItems(sf::RenderWindow &window) {
  for (int i = 0; i < m_items.size(); i++) {
    if (m_items[i] > 0) {
      window.draw(m_sprites[i]);
    }
  }
  if (m_activated[1]) {
    window.draw(m_timeFreezeBackdrop);
  }
}

void Items::activate(int x, int y, int wx) {
  int line = std::abs((x - (0.025987526 * wx)) / (0.1185031185 * wx));
  std::cout << line << std::endl;
  for (int i = 0; i < m_items.size(); i++) {
    if (selected == m_itemTypeOrder[i]) {
      if (m_items[i] > 0 &&
          m_sprites[i].getGlobalBounds().contains(sf::Vector2f(x, y))) {
        selected = ItemTypes::NONE;
        std::cout << "UNSELECT" << std::endl;
      } else {
        std::cout << "CLLICK" << std::endl;
        m_items[i]--;
        m_clocks[i].restart();
        m_activated[i] = true;
        switch (selected) {
        case ItemTypes::COLUMN_FREEZE:
          m_crates->freezeLine(line);
          break;
        case ItemTypes::TIME_SLOW:
          Clock::m_factor = 0.5;
          break;
        case ItemTypes::LINE_CLEAR:
          m_crates->clearLine(line);
          m_activated[i] = false;
          break;
        default:
          break;
        }
        selected = ItemTypes::NONE;
      }
    } else {
      if (m_items[i] > 0 &&
          m_sprites[i].getGlobalBounds().contains(sf::Vector2f(x, y))) {
        selected = m_itemTypeOrder[i];
      }
    }
  }
}

void Items::update() {
  for (int i = 0; i < m_activated.size(); i++) {
    if (m_activated[i] && m_clocks[i].getMilliSeconds() > 10000) {
      m_activated[i] = false;
      if (m_itemTypeOrder[i] == TIME_SLOW) {
        Clock::m_factor = 1;
      } else if (m_itemTypeOrder[i] == COLUMN_FREEZE) {
        m_crates->unfreezeLine();
      }
    }
  }
}

bool Items::isSelected() { return selected != ItemTypes::NONE; }