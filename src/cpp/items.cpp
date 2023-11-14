#include "items.hpp"
#include <random>

Items::Items(Crates *_crates, Grabber *_grabber, Spawner *_spawner) {
  m_items = {1, 1, 1};
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
  m_grabber = _grabber;
  m_spawner = _spawner;

  m_timeFreezeBackdrop.setSize(
      sf::Vector2f(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT));
  m_timeFreezeBackdrop.setFillColor(sf::Color(0, 0, 100, 30));

  eng = std::mt19937(rd());
  distr = std::uniform_int_distribution<int>(0, 2);
}

void Items::reset() {
  m_items = {0, 0, 0};
  m_activated = {false, false, false};
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
  switch (selected) {
  case LINE_CLEAR:
    m_sprites[2].setPosition(m_mousePos);
    break;
  case TIME_SLOW:
    m_sprites[1].setPosition(m_mousePos);
    break;
  case COLUMN_FREEZE:
    m_sprites[0].setPosition(m_mousePos);
    break;
  default:
    for (int i = 0; i < m_sprites.size(); i++) {
      m_sprites[i].setPosition(GameConstants::ITEMS_POS[i]);
    }
    break;
  }
}

void Items::activate(int ox, int x, int y, int wx) {
  int line = std::abs((ox - (0.025987526 * wx)) / (0.1185031185 * wx));
  for (int i = 0; i < m_items.size(); i++) {
    if (selected == m_itemTypeOrder[i]) {
      if (m_items[i] > 0 && y < GameConstants::BORDER_HEIGHT) {
        selected = ItemTypes::NONE;
      } else {
        if (!m_activated[i]) {
          m_activated[i] = true;
          m_clocks[i].restart();
          m_items[i]--;
          switch (selected) {
          case ItemTypes::COLUMN_FREEZE:
            m_crates->freezeLine(line);
            break;
          case ItemTypes::TIME_SLOW:
            m_crates->setClockFactor(0.5);
            m_spawner->setClockFactor(0.5);
            m_grabber->setClockFactor(0.5);
            break;
          case ItemTypes::LINE_CLEAR:
            m_crates->clearLine(line);
            m_activated[i] = false;
            break;
          default:
            break;
          }
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
        m_crates->setClockFactor(1);
        m_spawner->setClockFactor(1);
        m_grabber->setClockFactor(1);
      } else if (m_itemTypeOrder[i] == COLUMN_FREEZE) {
        m_crates->unfreezeLine();
      }
    }
  }
}

bool Items::isSelected() { return selected != ItemTypes::NONE; }

void Items::updateMousePos(sf::Vector2f pos) { m_mousePos = pos; }

void Items::addItem() { m_items[distr(eng)]++; }

void Items::play() {
  for (auto clock : m_clocks) {
    clock.play();
  }
}
void Items::pause() {
  for (auto clock : m_clocks) {
    clock.pause();
  }
}