#ifndef SCORER_H
#define SCORER_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "clock.hpp"
#include "constants.hpp"
#include "crates/crate.hpp"
#include <algorithm>
#include <fstream>
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

  struct ScoreMarker {
    sf::Text text;
    sf::Time initTime;
    sf::Vector2f initPos;
  };

  std::vector<ScoreMarker> m_scoreMarkers;

  std::fstream scoreFile;
  std::vector<int> key;

  int gcd(int a, int b);
  void extendedGCD(int a, int b, int &x, int &y);
  int modInverse(int a, int m);
  int mod(int a, int b);
  int c2i(char c);
  char i2c(int i);
  std::string encrypt(std::string raw, std::vector<int> key);
  std::string decrypt(std::string raw, std::vector<int> key);

public:
  Scorer();
  ~Scorer();
  void addScore(int score_add, sf::Vector2f pos);
  void addMergeScore(Crate *crate);
  void addExplodeScore(Crate *crate);
  void drawScore(sf::RenderWindow &window);
  void play();
  void pause();

  void reset();

  void readHighScore();
  void writeHighScore();
};

#endif