#ifndef CRATES_H
#define CRATES_H

#include "constants.hpp"
#include "crates/blueCrate.hpp"
#include "crates/bombCrate.hpp"
#include "crates/crate.hpp"
#include "crates/goldCrate.hpp"
#include "crates/greenCrate.hpp"
#include "crates/heavyCrate.hpp"
#include "crates/hyperBombCrate.hpp"
#include "crates/megaBombCrate.hpp"
#include "crates/multiColorCrate.hpp"
#include "crates/orangeCrate.hpp"
#include "crates/pinkCrate.hpp"
#include "crates/purpleCrate.hpp"
#include "crates/redCrate.hpp"
#include "crates/unbreakableCrate.hpp"
#include "crates/yellowCrate.hpp"
#include "scorer.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <vector>
using namespace std;

typedef vector<Crate *> crate_col;
typedef vector<crate_col> crate_matrix;

class Crates {
private:
  crate_matrix m_crates;
  Crate *m_grabbedCrate;
  vector<pair<Crate *, sf::Vector2f>> m_fadingInCrates;

  Scorer *m_scorer;

  set<int> frozenLines;

  sf::Vector2f getCratePos(int line, int row);
  Crate *getCrateFromEnum(GameConstants::CrateType type);
  bool isBomb(GameConstants::CrateType type);
  void updateCrates();
  void mergeCrates();
  void explodeCrate();
  bool explodeCrateRange(int line, int start, int end);
  int getRowIgnoringFadingIn(int column, int row);

public:
  Crates(Scorer *_scorer);
  ~Crates();
  bool linePlacable(int line);
  bool spawnCrate(int grabberLine, bool isActive);
  bool spawnCrate(int grabberLine, bool isActive,
                  GameConstants::CrateType type);
  bool placeCrate(int line, Crate *crate);
  bool isLineGrabbable(int line);
  void destroyCrate(int line, int row);
  void update();
  void drawCrates(sf::RenderWindow &window);
  float getTopCrateHeight(int line);
  float getNextCrateHeight(int line);

  bool grabCrate(int line);
  bool placeCrate(int line);
  bool setGrabbedCratePos(sf::Vector2f pos);

  void setClockFactor(float _factor);

  void clear();

  void clearLine(int line);
  void freezeLine(int line);
  void unfreezeLine();

  static Crate *makeCrate(Crate *crate);
};

#endif