#include "crates.hpp"

Crates::Crates(Scorer *_scorer) {
  m_crates = vector<crate_col>(8);
  m_grabbedCrate = nullptr;
  m_scorer = _scorer;
}

Crates::~Crates() {
  for (auto column : m_crates) {
    for (auto crate : column) {
      delete crate;
    }
  }
}

sf::Vector2f Crates::getCratePos(int line, int row) {
  return sf::Vector2f(line * 228 + 164, 1236 - row * 128);
}

bool Crates::linePlacable(int line) { return m_crates[line].size() < 6; }

bool Crates::spawnCrate(int grabberLine, bool isActive,
                        GameConstants::CrateType type) {
  vector<int> spawnableLines;
  for (int i = 0; i < m_crates.size(); i++) {
    if (linePlacable(i) && (!isActive || i != grabberLine)) {
      if (m_crates[i].size() == 0) {
        spawnableLines.push_back(i);
      } else if (m_crates[i].back()->getPos().y >
                 GameConstants::SPAWN_HEIGHT + GameConstants::CRATE_SIZE.y) {
        spawnableLines.push_back(i);
      }
    }
  }
  if (spawnableLines.size() == 0)
    return false;

  std::vector<int> out;
  size_t nelems = 1;
  std::sample(spawnableLines.begin(), spawnableLines.end(),
              std::back_inserter(out), nelems,
              std::mt19937{std::random_device{}()});
  Crate *tempCrate;
  tempCrate = getCrateFromEnum(type);
  if (tempCrate == nullptr)
    return false;
  tempCrate->setState(Crate::CrateState::SPAWNING);
  m_crates[out[0]].push_back(tempCrate);

  return true;
}

bool Crates::spawnCrate(int grabberLine, bool isActive) {
  return spawnCrate(grabberLine, isActive,
                    GameConstants::CrateType::PURPLE_CRATE);
}

bool Crates::placeCrate(int line, Crate *crate) {
  if (!linePlacable(line)) {
    delete crate;
    return false;
  }
  m_crates[line].push_back(crate);
  return true;
}

bool Crates::isLineGrabbable(int line) {
  if (m_crates[line].size() > 0) {
    return m_crates[line].back()->moveable();
  }
  return false;
}

void Crates::destroyCrate(int line, int row) {
  delete m_crates[line][row];
  m_crates[line].erase(m_crates[line].begin() + row);
  for (auto crate : m_fadingInCrates) {
    if (crate.second.x == line && crate.second.y > row) {
      crate.second.y--;
    }
  }
}

void Crates::clearLine(int line) {
  for (int i = 0; i < m_crates[line].size(); i++) {
    delete m_crates[line][i];
  }
  m_crates[line].clear();
}

void Crates::freezeLine(int line) { frozenLines.insert(line); }

void Crates::unfreezeLine() { frozenLines.erase(frozenLines.begin()); }

void Crates::clear() {
  for (int column = 0; column < m_crates.size(); column++) {
    for (int i = m_crates[column].size() - 1; i >= 0; i--) {
      destroyCrate(column, i);
    }
  }
}

int Crates::getRowIgnoringFadingIn(int column, int row) {
  int temp = 0;
  for (int i = 0; i <= row; i++) {
    if (m_crates[column][i]->getState() != Crate::CrateState::FADINGIN) {
      temp++;
    }
  }
  return temp - 1;
}

void Crates::update() {
  mergeCrates();
  explodeCrate();
  updateCrates();
}

void Crates::updateCrates() {
  for (int column = 0; column < m_crates.size(); column++) {
    if (frozenLines.find(column) != frozenLines.end()) {
      continue;
    }
    for (int i = m_crates[column].size() - 1; i >= 0; i--) {
      Crate *currentCrate = m_crates[column][i];
      float temp;
      int row = getRowIgnoringFadingIn(column, i);

      switch (currentCrate->getState()) {
      case Crate::CrateState::SPAWNING:
        currentCrate->setPosition(GameConstants::SPAWN_POS[column]);
        temp =
            (GameConstants::CRATE_SIZE.x / GameConstants::CRATE_GROWTH_TIME) *
            currentCrate->getElapsedTime().asMilliseconds();
        if (currentCrate->getElapsedTime().asMilliseconds() >
            GameConstants::CRATE_GROWTH_TIME) {
          temp = GameConstants::CRATE_SIZE.x;
          currentCrate->restartClock();
          currentCrate->setState(Crate::CrateState::FALLING);
          currentCrate->setInitHeight(GameConstants::SPAWN_HEIGHT);
        }
        currentCrate->setSize(sf::Vector2f(temp, temp));
        break;
      case Crate::CrateState::IDLE:
        if (currentCrate->getPos().y != GameConstants::ROW_Y[row]) {
          currentCrate->setState(Crate::CrateState::FALLING);
          currentCrate->restartClock();
          currentCrate->setInitHeight(currentCrate->getPos().y);
        } else
          currentCrate->setPosition(sf::Vector2f(
              GameConstants::COLUMN_X[column], GameConstants::ROW_Y[row]));
        break;
      case Crate::CrateState::FALLING:
        temp =
            GameConstants::CRATE_FALLING_ACCELERATION *
                std::pow(currentCrate->getElapsedTime().asMilliseconds(), 2) +
            currentCrate->getInitHeight();
        if (row > 0) {
          temp = std::min(temp, m_crates[column][row - 1]->getPos().y -
                                    GameConstants::CRATE_SIZE.y);
        }
        if (temp >= GameConstants::ROW_Y[row]) {
          temp = GameConstants::ROW_Y[row];
          currentCrate->restartClock();
          currentCrate->setState(Crate::CrateState::IDLE);
        }
        currentCrate->setPosition(GameConstants::SPAWN_POS[column].x, temp);
        break;
      case Crate::CrateState::FADINGOUT:
        if (currentCrate->getElapsedTime().asMilliseconds() >
            GameConstants::CRATE_FADE_TIME) {
          destroyCrate(column, i);
          // for (int i = m_fadingInCrates.size() - 1; i >= 0; i--) {
          //   if (column == m_fadingInCrates[i].second.x &&
          //       row == m_fadingInCrates[i].second.y) {
          //     m_crates[column].insert(m_crates[column].begin() + row,
          //                             m_fadingInCrates[i].first);
          //     m_fadingInCrates[i].first->setState(Crate::CrateState::FALLING);
          //     m_fadingInCrates[i].first->restartClock();
          //     m_fadingInCrates[i].first->setInitHeight(
          //         GameConstants::ROW_Y[m_fadingInCrates[i].second.y]);
          //     m_fadingInCrates.erase(m_fadingInCrates.begin() + i);
          //   }
          // }
        }
        temp = GameConstants::CRATE_SIZE.x -
               (GameConstants::CRATE_SIZE.x / GameConstants::CRATE_FADE_TIME) *
                   currentCrate->getElapsedTime().asMilliseconds();
        currentCrate->setSize(sf::Vector2f(temp, temp));
        currentCrate->setAlpha(
            255 - (255 / GameConstants::CRATE_FADE_TIME) *
                      currentCrate->getElapsedTime().asMilliseconds());
        break;
      case Crate::CrateState::FADINGIN:
        currentCrate->setPosition(sf::Vector2f(GameConstants::COLUMN_X[column],
                                               GameConstants::ROW_Y[row]));
        if (currentCrate->getElapsedTime().asMilliseconds() >
            GameConstants::CRATE_FADE_TIME) {
          currentCrate->setState(Crate::CrateState::FALLING);
          currentCrate->restartClock();
          currentCrate->setInitHeight(GameConstants::ROW_Y[row]);
          currentCrate->setAlpha(255);
          currentCrate->setSize(GameConstants::CRATE_SIZE);
          // m_crates[column].insert(
          //     m_crates[column].begin() +
          //         row - 1,
          //     currentCrate);
          // m_fadingInCrates.erase(m_fadingInCrates.begin() + i);
        } else {
          temp =
              (GameConstants::CRATE_SIZE.x / GameConstants::CRATE_FADE_TIME) *
              currentCrate->getElapsedTime().asMilliseconds();
          currentCrate->setSize(sf::Vector2f(temp, temp));
          currentCrate->setAlpha(
              (255 / GameConstants::CRATE_FADE_TIME) *
              currentCrate->getElapsedTime().asMilliseconds());
        }
        break;
      default:
        break;
      }
    }
  }

  // float temp;
  // for (int i = m_fadingInCrates.size() - 1; i >= 0; i--) {
  //   m_fadingInCrates[i].first->setPosition(
  //       sf::Vector2f(GameConstants::COLUMN_X[m_fadingInCrates[i].second.x],
  //                    GameConstants::ROW_Y[m_fadingInCrates[i].second.y]));
  //   if (m_fadingInCrates[i].first->getElapsedTime().asMilliseconds() >
  //       GameConstants::CRATE_FADE_TIME) {
  //     std::cout << m_fadingInCrates[i].second.y << std::endl;
  //     m_fadingInCrates[i].first->setState(Crate::CrateState::FALLING);
  //     m_fadingInCrates[i].first->restartClock();
  //     m_fadingInCrates[i].first->setInitHeight(
  //         GameConstants::ROW_Y[m_fadingInCrates[i].second.y]);
  //     m_fadingInCrates[i].first->setAlpha(255);
  //     m_fadingInCrates[i].first->setSize(GameConstants::CRATE_SIZE);
  //     // m_crates[m_fadingInCrates[i].second.x].insert(
  //     //     m_crates[m_fadingInCrates[i].second.x].begin() +
  //     //         m_fadingInCrates[i].second.y - 1,
  //     //     m_fadingInCrates[i].first);
  //     // m_fadingInCrates.erase(m_fadingInCrates.begin() + i);
  //   } else {
  //     temp = (GameConstants::CRATE_SIZE.x / GameConstants::CRATE_FADE_TIME) *
  //            m_fadingInCrates[i].first->getElapsedTime().asMilliseconds();
  //     m_fadingInCrates[i].first->setSize(sf::Vector2f(temp, temp));
  //     m_fadingInCrates[i].first->setAlpha(
  //         (255 / GameConstants::CRATE_FADE_TIME) *
  //         m_fadingInCrates[i].first->getElapsedTime().asMilliseconds());
  //   }
  // }
}

void Crates::mergeCrates() {
  for (int column = 0; column < GameConstants::CRATE_COLUMNS; column++) {
    crate_col &currentColumn = m_crates[column];
    vector<std::pair<int, GameConstants::CrateType>> toMerge;
    if (currentColumn.size() >= 3) {
      for (int i = 1; i < currentColumn.size() - 1; i++) {
        if (currentColumn[i - 1]->getState() == Crate::CrateState::IDLE &&
            currentColumn[i]->getState() == Crate::CrateState::IDLE &&
            currentColumn[i + 1]->getState() == Crate::CrateState::IDLE) {
          std::set<GameConstants::CrateType> crates;
          Crate *crate;
          for (int j = -1; j <= 1; j++) {
            if (currentColumn[i + j]->getCrateType() !=
                GameConstants::CrateType::MULTICOLOR_CRATE) {
              crates.insert(currentColumn[i + j]->getCrateType());
              crate = currentColumn[i + j];
            }
          }
          if (crates.size() <= 1) {
            if (crates.size() == 0)
              crate = currentColumn[i];

            m_scorer->addMergeScore(currentColumn[i]);
            currentColumn[i - 1]->setState(Crate::CrateState::FADINGOUT);
            currentColumn[i]->setState(Crate::CrateState::FADINGOUT);
            currentColumn[i + 1]->setState(Crate::CrateState::FADINGOUT);
            currentColumn[i - 1]->restartClock();
            currentColumn[i]->restartClock();
            currentColumn[i + 1]->restartClock();
            // currentColumn[i]->setMerged();
            // toMerge.push_back(std::make_pair(i,
            // currentColumn[i]->nextCrate()));
            Crate *tempCrate = getCrateFromEnum(crate->nextCrate());
            if (tempCrate != nullptr) {
              tempCrate->setState(Crate::CrateState::FADINGIN);
              tempCrate->restartClock();
              tempCrate->setInitHeight(GameConstants::ROW_Y[i]);
              currentColumn.insert(currentColumn.begin() + i + 1, tempCrate);
              // m_fadingInCrates.push_back(
              //     make_pair(tempCrate, sf::Vector2f(column, i)));
            }
          }
        }
      }
    }
    for (auto item : toMerge) {
      Crate *tempCrate = getCrateFromEnum(item.second);
      if (tempCrate == nullptr)
        continue;
      tempCrate->setState(Crate::CrateState::FALLING);
      tempCrate->restartClock();
      tempCrate->setInitHeight(GameConstants::ROW_Y[item.first]);
      m_scorer->addMergeScore(m_crates[column][item.first]);
      destroyCrate(column, item.first + 1);
      destroyCrate(column, item.first);
      destroyCrate(column, item.first - 1);
      currentColumn.insert(currentColumn.begin() + item.first - 1, tempCrate);
    }
  }
}

void Crates::explodeCrate() {
  for (int column = 0; column < GameConstants::CRATE_COLUMNS; column++) {
    for (int row = 0; row < m_crates[column].size(); row++) {
      Crate *currentCrate = m_crates[column][row];
      if (isBomb(currentCrate->getCrateType())) {
        if (currentCrate->isExploded()) {
          switch (currentCrate->getCrateType()) {
          case GameConstants::CrateType::BOMB_CRATE:
            explodeCrateRange(column, row + 1, row - 1);
            break;
          case GameConstants::CrateType::MEGA_BOMB_CRATE:
            explodeCrateRange(column - 1, row + 1, row - 1);
            explodeCrateRange(column, row + 2, row - 2);
            explodeCrateRange(column + 1, row + 1, row - 1);
            break;
          case GameConstants::CrateType::HYPER_BOMB_CRATE:
            explodeCrateRange(column - 2, row + 1, row - 1);
            explodeCrateRange(column - 1, row + 2, row - 2);
            explodeCrateRange(column, row + 3, row - 3);
            explodeCrateRange(column + 1, row + 2, row - 2);
            explodeCrateRange(column + 2, row + 1, row - 1);
            break;
          default:
            break;
          }
          return;
        }
      }
    }
  }
}

void Crates::setClockFactor(float _factor) {
  for (auto i : m_crates) {
    for (auto j : i) {
      j->setClockFactor(_factor);
    }
  }
}

bool Crates::explodeCrateRange(int line, int _start, int _end) {
  if (line >= 0 && line < GameConstants::CRATE_COLUMNS) {
    int start, end;
    start = std::max(_start, _end);
    end = std::min(_start, _end);
    for (int row = start + 1; row < m_crates[line].size(); row++) {
      if (m_crates[line][row]->getState() == Crate::CrateState::IDLE) {
        m_crates[line][row]->restartClock();
        m_crates[line][row]->setState(Crate::CrateState::FALLING);
        m_crates[line][row]->setInitHeight(GameConstants::ROW_Y[row]);
      }
    }
    for (int row = start; row >= end; row--) {
      if (m_crates[line].size() > row) {
        if (m_crates[line][row]->getState() == Crate::CrateState::IDLE) {
          if (m_crates[line][row]->explodable()) {
            m_crates[line][row]->setState(Crate::CrateState::FADINGOUT);
            m_crates[line][row]->restartClock();
            m_scorer->addExplodeScore(m_crates[line][row]);
          } else {
            m_crates[line][row]->setState(Crate::CrateState::FALLING);
            m_crates[line][row]->setInitHeight(GameConstants::ROW_Y[row]);
            m_crates[line][row]->restartClock();
          }
        }
      }
    }
    return true;
  }
  return false;
}

void Crates::drawCrates(sf::RenderWindow &window) {
  for (std::vector<Crate *> column : m_crates) {
    for (Crate *crate : column) {
      crate->drawCrate(window);
    }
  }
  for (auto crate : m_fadingInCrates) {
    crate.first->drawCrate(window);
  }
  if (m_grabbedCrate != nullptr)
    m_grabbedCrate->drawCrate(window);
}

float Crates::getTopCrateHeight(int line) {
  if (m_crates[line].size() == 0)
    return 0;
  return m_crates[line].back()->getPos().y;
}

float Crates::getNextCrateHeight(int line) {
  if (m_crates[line].size() == 0)
    return GameConstants::ROW_Y[0];
  return m_crates[line].back()->getPos().y - GameConstants::CRATE_SIZE.y;
}

Crate *Crates::makeCrate(Crate *crate) {
  Crate *temp(crate);
  return temp;
}

bool Crates::grabCrate(int line) {
  if (m_crates[line].size() == 0)
    return false;
  switch (m_crates[line].back()->getState()) {
  case Crate::CrateState::FALLING:
  case Crate::CrateState::IDLE:
    m_grabbedCrate = m_crates[line].back();
    m_crates[line].erase(m_crates[line].end() - 1);
    return true;
  default:
    break;
  }
  return false;
}

bool Crates::placeCrate(int line) {
  if (m_crates[line].size() == GameConstants::CRATES_PER_LINE)
    return false;
  m_grabbedCrate->setState(Crate::CrateState::FALLING);
  m_grabbedCrate->restartClock();
  m_grabbedCrate->setInitHeight(m_grabbedCrate->getPos().y);
  m_crates[line].push_back(m_grabbedCrate);
  m_grabbedCrate = nullptr;
  return true;
}

bool Crates::setGrabbedCratePos(sf::Vector2f pos) {
  if (m_grabbedCrate == nullptr)
    return false;
  m_grabbedCrate->setPosition(pos);
  return true;
}

Crate *Crates::getCrateFromEnum(GameConstants::CrateType type) {
  Crate *tempCrate;
  switch (type) {
  case GameConstants::CrateType::PURPLE_CRATE:
    tempCrate = new PurpleCrate();
    break;
  case GameConstants::CrateType::BLUE_CRATE:
    tempCrate = new BlueCrate();
    break;
  case GameConstants::CrateType::GREEN_CRATE:
    tempCrate = new GreenCrate();
    break;
  case GameConstants::CrateType::YELLOW_CRATE:
    tempCrate = new YellowCrate();
    break;
  case GameConstants::CrateType::ORANGE_CRATE:
    tempCrate = new OrangeCrate();
    break;
  case GameConstants::CrateType::RED_CRATE:
    tempCrate = new RedCrate();
    break;
  case GameConstants::CrateType::PINK_CRATE:
    tempCrate = new PinkCrate();
    break;
  case GameConstants::CrateType::GOLD_CRATE:
    tempCrate = new GoldCrate();
    break;
  case GameConstants::CrateType::BOMB_CRATE:
    tempCrate = new BombCrate();
    break;
  case GameConstants::CrateType::MEGA_BOMB_CRATE:
    tempCrate = new MegaBombCrate();
    break;
  case GameConstants::CrateType::HYPER_BOMB_CRATE:
    tempCrate = new HyperBombCrate();
    break;
  case GameConstants::CrateType::UNBREAKABLE_CRATE:
    tempCrate = new UnbreakableCrate();
    break;
  case GameConstants::CrateType::HEAVY_CRATE:
    tempCrate = new HeavyCrate();
    break;
  case GameConstants::CrateType::MULTICOLOR_CRATE:
    tempCrate = new MultiColorCrate();
    break;
  default:
    tempCrate = nullptr;
  }
  return tempCrate;
}

bool Crates::isBomb(GameConstants::CrateType type) {
  switch (type) {
  case GameConstants::CrateType::BOMB_CRATE:
  case GameConstants::CrateType::MEGA_BOMB_CRATE:
  case GameConstants::CrateType::HYPER_BOMB_CRATE:
    return true;
  default:
    return false;
  }
}