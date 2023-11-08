#ifndef SCORER_H
#define SCORER_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "clock.hpp"
#include "constants.hpp"
#include "crates/crate.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Scorer {
private:
  int m_scoreNum;
  int m_highScoreNum;

  sf::Text m_score;
  sf::Text m_highScore;

  Clock m_clock;

  std::vector<std::pair<sf::Text, int>> m_scoreMarkers;

public:
  Scorer();
  void addScore(int score_add, sf::Vector2f pos);
  void addMergeScore(Crate *crate);
  void addExplodeScore(Crate *crate);
  void drawScore(sf::RenderWindow &window);
};

#endif