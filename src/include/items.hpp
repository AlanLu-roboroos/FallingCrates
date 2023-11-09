#ifndef ITEMS_HPP
#define ITEMS_HPP

#include "SFML/Graphics.hpp"
#include "clock.hpp"
#include "constants.hpp"
#include "crates.hpp"
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

public:
  Items(Crates *_crates);
  void drawItems(sf::RenderWindow &window);
  void activate(int x, int y, int wx);
  void update();
  bool isSelected();
  void updateMousePos(sf::Vector2f pos);
};

#endif