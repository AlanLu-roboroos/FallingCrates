#ifndef ITEMS_HPP
#define ITEMS_HPP

#include "SFML/Graphics.hpp"
#include "items/item.hpp"
#include <vector>

typedef std::pair<Item *, int> item;

class Items {
private:
  std::vector<item> m_items;

public:
  Items();
  void drawItems();
};

#endif