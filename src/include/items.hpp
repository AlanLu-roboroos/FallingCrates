#ifndef ITEMS_HPP
#define ITEMS_HPP

#include "SFML/Graphics.hpp"
#include "clock.hpp"
#include "constants.hpp"
#include "crates.hpp"
#include "grabber.hpp"
#include "spawner.hpp"
#include <iostream>
#include <vector>

class Items {
  enum ItemTypes { LINE_CLEAR, COLUMN_FREEZE, TIME_SLOW, NONE };

private:
  std::vector<ItemTypes> m_itemTypeOrder;
  std::vector<int> m_items;
  std::vector<Clock> m_clocks;
  std::vector<sf::Sprite> m_sprites;
  std::vector<bool> m_activated;
  ItemTypes selected;
  sf::Vector2f m_mousePos;

  sf::RectangleShape m_timeFreezeBackdrop;

  Crates *m_crates;
  Grabber *m_grabber;
  Spawner *m_spawner;

  std::random_device rd;
  std::mt19937 eng;
  std::uniform_int_distribution<> distr;

public:
  Items(Crates *_crates, Grabber *_grabber, Spawner *_spawner);
  void reset();
  void drawItems(sf::RenderWindow &window);
  void activate(int ox, int x, int y, int wx);
  void update();
  bool isSelected();
  void updateMousePos(sf::Vector2f pos);
  void addItem();

  void play();
  void pause();
};

#endif