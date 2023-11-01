#ifndef CRATES_H
#define CRATES_H

#include "constants.hpp"
#include "crates/crate.hpp"
#include <memory>
#include <vector>
using namespace std;

class Crates {
private:
  vector<vector<shared_ptr<Crate>>> crates;

public:
  bool linePlacable(int line);
  bool placeCrate(int line, std::shared_ptr<Crate> crate);
  std::shared_ptr<Crate> removeCrate(int line);
  void update();
};

#endif