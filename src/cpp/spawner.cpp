#include "spawner.hpp"

Spawner::Spawner() { reset(); }

void Spawner::reset() {
  m_clock.restart();
  m_lastTime = 0;
  first = true;

  m_cratesTargets[CrateType::PURPLE_CRATE] = 0.5;
  m_cratesTargets[CrateType::BLUE_CRATE] = 0.4;
  m_cratesTargets[CrateType::GREEN_CRATE] = 0.04;
  m_cratesTargets[CrateType::YELLOW_CRATE] = 0.03;
  m_cratesTargets[CrateType::ORANGE_CRATE] = 0.01;
  m_cratesTargets[CrateType::RED_CRATE] = 0.008;
  m_cratesTargets[CrateType::PINK_CRATE] = 0.007;
  m_cratesTargets[CrateType::GOLD_CRATE] = 0.005;

  m_cratesTargets[CrateType::BOMB_CRATE] = 0.6;
  m_cratesTargets[CrateType::MEGA_BOMB_CRATE] = 0.3;
  m_cratesTargets[CrateType::HYPER_BOMB_CRATE] = 0.1;

  m_cratesTargets[CrateType::MULTICOLOR_CRATE] = 0.3;
  m_cratesTargets[CrateType::HEAVY_CRATE] = 0.3;
  m_cratesTargets[CrateType::UNBREAKABLE_CRATE] = 0.3;
  m_cratesTargets[CrateType::VIRUS_CRATE] = 0.1;

  m_normalCrates = {CrateType::PURPLE_CRATE, CrateType::BLUE_CRATE};
  m_bombCrates = {CrateType::BOMB_CRATE};
  m_otherCrates = {CrateType::MULTICOLOR_CRATE, CrateType::HEAVY_CRATE,
                   CrateType::UNBREAKABLE_CRATE, CrateType::VIRUS_CRATE};

  m_normalCratesTarget = {CrateType::PURPLE_CRATE, CrateType::BLUE_CRATE,
                          CrateType::GREEN_CRATE,  CrateType::YELLOW_CRATE,
                          CrateType::ORANGE_CRATE, CrateType::RED_CRATE,
                          CrateType::PINK_CRATE,   CrateType::GOLD_CRATE};
  m_bombCratesTarget = {CrateType::BOMB_CRATE, CrateType::MEGA_BOMB_CRATE,
                        CrateType::HYPER_BOMB_CRATE};
  m_otherCratesTarget = {CrateType::MULTICOLOR_CRATE, CrateType::HEAVY_CRATE,
                         CrateType::UNBREAKABLE_CRATE, CrateType::VIRUS_CRATE};

  gen.seed(rd());
  m_type.param({0.90, 0.08, 0.02});
}

GameConstants::CrateType Spawner::update(std::set<CrateType> seenCrates) {
  for (auto crate : seenCrates) {
    if (std::find(m_normalCratesTarget.begin(), m_normalCratesTarget.end(),
                  crate) != m_normalCratesTarget.end()) {
      if (std::find(m_normalCrates.begin(), m_normalCrates.end(), crate) ==
          m_normalCrates.end()) {
        m_normalCrates.push_back(crate);
      }
    } else if (std::find(m_bombCratesTarget.begin(), m_bombCratesTarget.end(),
                         crate) != m_bombCratesTarget.end()) {
      if (std::find(m_bombCrates.begin(), m_bombCrates.end(), crate) ==
          m_bombCrates.end()) {
        m_bombCrates.push_back(crate);
      }
    } else if (std::find(m_otherCratesTarget.begin(), m_otherCratesTarget.end(),
                         crate) != m_otherCratesTarget.end()) {
      if (std::find(m_otherCrates.begin(), m_otherCrates.end(), crate) ==
          m_otherCrates.end()) {
        m_otherCrates.push_back(crate);
      }
    }
  }

  // for (auto crate : m_normalCrates) {
  //   std::cout << crate << std::endl;
  // }

  if (m_clock.getMilliSeconds() - m_lastTime >
      getSpawnTime().asMilliseconds()) {
    m_lastTime = m_clock.getElapsedTime().asMilliseconds();
    if (first)
      first = false;

    CrateType crate = CrateType::NONE;
    m_probabilities.clear();

    int type = m_type(gen);

    if (type == 0) {
      for (auto crate : m_normalCrates) {
        m_probabilities.push_back(m_cratesTargets[crate]);
      }
      std::discrete_distribution<CrateType> d(m_probabilities.begin(),
                                              m_probabilities.end());
      crate = m_normalCrates[d(gen)];
    } else if (type == 1) {
      for (auto crate : m_bombCrates) {
        m_probabilities.push_back(m_cratesTargets[crate]);
      }
      std::discrete_distribution<CrateType> d(m_probabilities.begin(),
                                              m_probabilities.end());
      crate = m_bombCrates[d(gen)];

    } else if (type == 2) {
      for (auto crate : m_otherCrates) {
        m_probabilities.push_back(m_cratesTargets[crate]);
      }
      std::discrete_distribution<CrateType> d(m_probabilities.begin(),
                                              m_probabilities.end());
      crate = m_otherCrates[d(gen)];
    }
    return crate;
  }
  return GameConstants::CrateType::NONE;
}

void Spawner::setClockFactor(float _factor) { m_clock.setFactor(_factor); }

void Spawner::play() { m_clock.play(); }
void Spawner::pause() { m_clock.pause(); }

sf::Time Spawner::getSpawnTime() {
  if (first)
    return sf::milliseconds(200);
  sf::Time temp;
  temp = sf::milliseconds(
      2000 -
      1000 /
          (1 + std::exp(-0.00008 *
                        (m_clock.getElapsedTime().asMilliseconds() - 30000))) -
      0.0005 * m_clock.getMilliSeconds());
  return temp;
}