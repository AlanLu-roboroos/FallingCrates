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

bool Crates::spawnCrate(int grabberLine, bool isActive) {
  vector<int> spawnableLines;
  std::cout << grabberLine << std::endl;
  for (int i = 0; i < crates.size(); i++) {
    if (linePlacable(i) && (!isActive || i != grabberLine))
      spawnableLines.push_back(i);
  }
  if (spawnableLines.size() == 0)
    return false;

  std::vector<int> out;
  size_t nelems = 1;
  std::sample(spawnableLines.begin(), spawnableLines.end(),
              std::back_inserter(out), nelems,
              std::mt19937{std::random_device{}()});
  crates[out[0]].push_back(new PurpleCrate());

  return true;
}

bool Crates::placeCrate(int line, Crate *crate) {
  if (!linePlacable(line)) {
    delete crate;
    return false;
  }
  crates[line].push_back(crate);
  return true;
}

bool Crates::isLineGrabbable(int line) { return crates[line].size() > 0; }

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