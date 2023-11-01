#include "crates.hpp"

Crates::Crates() { crates = vector<crate_col>(8); }

Crates::~Crates() {
  for (auto column : crates) {
    for (auto crate : column) {
      delete crate;
    }
  }
}

sf::Vector2f Crates::getCratePos(int line, int row) {
  return sf::Vector2f(line * 228 + 164, 1236 - row * 128);
}

bool Crates::linePlacable(int line) { return crates[line].size() < 6; }
bool Crates::placeCrate(int line, Crate *crate) {
  if (!linePlacable(line)) {
    delete crate;
    return false;
  }
  std::cout << "testin" << std::endl;
  crates[line].push_back(crate);
  return true;
}

Crate *Crates::popCrate(int line) {
  Crate *temp = crates[line].back();
  crates[line].pop_back();
  return temp;
}

void Crates::destroyCrate(int line, int row) {
  delete crates[line][row];
  crates[line].erase(crates[line].begin() + row);
}

void Crates::update() {
  for (int column = 0; column < crates.size(); column++) {
    for (int row = 0; row < crates[column].size(); row++) {
      crates[column][row]->setPosition(getCratePos(column, row));
    }
  }
}

void Crates::drawCrates(sf::RenderWindow &window) {
  for (std::vector<Crate *> column : crates) {
    for (Crate *crate : column) {
      crate->drawCrate(window);
    }
  }
}

Crate *Crates::makeCrate(Crate *crate) {
  Crate *temp(crate);
  return temp;
}