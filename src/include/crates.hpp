#ifndef CRATES_H
#define CRATES_H

#include "constants.hpp"
#include "crates/crate.hpp"
#include "crates/purpleCrate.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
using namespace std;

typedef vector<Crate *> crate_col;
typedef vector<crate_col> crate_matrix;

class Crates {
private:
  crate_matrix crates;

  sf::Vector2f getCratePos(int line, int row);

public:
  Crates();
  ~Crates();
  bool linePlacable(int line);
  bool spawnCrate(int grabberLine, bool isActive);
  bool placeCrate(int line, Crate *crate);
  bool isLineGrabbable(int line);
  Crate *popCrate(int line);
  void destroyCrate(int line, int row);
  void update();
  void drawCrates(sf::RenderWindow &window);

  static Crate *makeCrate(Crate *crate);
};

#endif