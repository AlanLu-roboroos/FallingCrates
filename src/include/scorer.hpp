#ifndef SCORER_H
#define SCORER_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "constants.hpp"
#include "crates/crate.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Scorer {
private:
  int scoreNum;
  int highScoreNum;

  sf::Text score;
  sf::Text highScore;

  sf::Clock clock;

  std::vector<std::pair<sf::Text, int>> scoreMarkers;

public:
  Scorer();
  void addScore(int score_add, sf::Vector2f pos);
  void addMergeScore(Crate *crate);
  void addExplodeScore(Crate *crate);
  void drawScore(sf::RenderWindow &window);
};

#endif