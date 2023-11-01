#include "crates.hpp"

bool Crates::linePlacable(int line) { return crates[line].size() < 6; }
bool Crates::placeCrate(int line, std::shared_ptr<Crate> crate) {
  if (!linePlacable(line))
    return 1;
  crates[line].push_back(crate);
  return 0;
}