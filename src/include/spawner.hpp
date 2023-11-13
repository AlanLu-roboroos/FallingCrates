#ifndef SPAWNER_H
#define SPAWNER_H

#include "SFML/Graphics.hpp"
#include "clock.hpp"
#include "constants.hpp"
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <vector>

typedef GameConstants::CrateType CrateType;

class Spawner {
private:
  Clock m_clock;
  float m_lastTime;
  bool first;

  std::discrete_distribution<int> m_type;

  std::vector<float> m_probabilities;

  std::vector<GameConstants::CrateType> m_otherCrates;
  std::vector<GameConstants::CrateType> m_normalCrates;
  std::vector<GameConstants::CrateType> m_bombCrates;

  std::vector<GameConstants::CrateType> m_otherCratesTarget;
  std::vector<GameConstants::CrateType> m_normalCratesTarget;
  std::vector<GameConstants::CrateType> m_bombCratesTarget;

  std::map<GameConstants::CrateType, float> m_cratesTargets;

  std::random_device rd;
  std::mt19937 gen;

  sf::Time getSpawnTime();

public:
  Spawner();
  void reset();
  GameConstants::CrateType update(std::set<CrateType> seenCrates);
  void setClockFactor(float _factor);
  void play();
  void pause();
};

#endif