#include "crates.hpp"

Crates::Crates(Scorer *_scorer) {
  crates = vector<crate_col>(8);
  grabbedCrate = nullptr;
  scorer = _scorer;
}

Crates::~Crates() {
  for (auto column : crates) {
    for (auto crate : column) {
      delete crate;
    }
  }
}

sf::Vector2f Crates::getCratePos(int line, int row) {
  return sf::Vector2f(line * 228 + 164, 1236 - row * 128);
}

bool Crates::linePlacable(int line) { return crates[line].size() < 6; }

bool Crates::spawnCrate(int grabberLine, bool isActive,
                        GameConstants::CrateType type) {
  vector<int> spawnableLines;
  for (int i = 0; i < crates.size(); i++) {
    if (linePlacable(i) && (!isActive || i != grabberLine)) {
      if (crates[i].size() == 0) {
        spawnableLines.push_back(i);
      } else if (crates[i].back()->getPos().y >
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
  crates[out[0]].push_back(tempCrate);

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
  crates[line].push_back(crate);
  return true;
}

bool Crates::isLineGrabbable(int line) {
  if (crates[line].size() > 0) {
    return crates[line].back()->moveable();
  }
  return false;
}

void Crates::destroyCrate(int line, int row) {
  delete crates[line][row];
  crates[line].erase(crates[line].begin() + row);
}
void Crates::clear() {
  for (int column = 0; column < crates.size(); column++) {
    for (int i = crates[column].size() - 1; i >= 0; i--) {
      destroyCrate(column, i);
    }
  }
}

void Crates::update() {
  updateCrates();
  mergeCrates();
  explodeCrate();
}

void Crates::updateCrates() {
  for (int column = 0; column < crates.size(); column++) {
    for (int row = crates[column].size() - 1; row >= 0; row--) {
      Crate *currentCrate = crates[column][row];
      float temp;

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
          temp = std::min(temp, crates[column][row - 1]->getPos().y -
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
          destroyCrate(column, row);
          for (int i = fadingInCrates.size() - 1; i >= 0; i--) {
            if (column == fadingInCrates[i].second.x &&
                row == fadingInCrates[i].second.y) {
              crates[column].insert(crates[column].begin() + row,
                                    fadingInCrates[i].first);
              fadingInCrates[i].first->setState(Crate::CrateState::FALLING);
              fadingInCrates[i].first->restartClock();
              fadingInCrates[i].first->setInitHeight(
                  GameConstants::ROW_Y[fadingInCrates[i].second.y]);
              fadingInCrates.erase(fadingInCrates.begin() + i);
            }
          }
        }
        temp = GameConstants::CRATE_SIZE.x -
               (GameConstants::CRATE_SIZE.x / GameConstants::CRATE_FADE_TIME) *
                   currentCrate->getElapsedTime().asMilliseconds();
        currentCrate->setSize(sf::Vector2f(temp, temp));
        currentCrate->setAlpha(
            255 - (255 / GameConstants::CRATE_FADE_TIME) *
                      currentCrate->getElapsedTime().asMilliseconds());
        break;
      default:
        break;
      }
    }
  }

  float temp;
  for (auto currentCrate : fadingInCrates) {
    currentCrate.first->setPosition(
        sf::Vector2f(GameConstants::COLUMN_X[currentCrate.second.x],
                     GameConstants::ROW_Y[currentCrate.second.y]));
    if (currentCrate.first->getElapsedTime().asMilliseconds() >
        GameConstants::CRATE_FADE_TIME) {
      currentCrate.first->setState(Crate::CrateState::FALLING);
      currentCrate.first->restartClock();
      currentCrate.first->setInitHeight(
          GameConstants::ROW_Y[currentCrate.second.y]);
      currentCrate.first->setAlpha(255);
      currentCrate.first->setSize(GameConstants::CRATE_SIZE);
    } else {
      temp = (GameConstants::CRATE_SIZE.x / GameConstants::CRATE_FADE_TIME) *
             currentCrate.first->getElapsedTime().asMilliseconds();
      currentCrate.first->setSize(sf::Vector2f(temp, temp));
      currentCrate.first->setAlpha(
          (255 / GameConstants::CRATE_FADE_TIME) *
          currentCrate.first->getElapsedTime().asMilliseconds());
    }
  }
}

void Crates::mergeCrates() {
  for (int column = 0; column < GameConstants::CRATE_COLUMNS; column++) {
    crate_col &currentColumn = crates[column];
    vector<std::pair<int, GameConstants::CrateType>> toMerge;
    if (currentColumn.size() >= 3) {
      for (int i = 1; i < currentColumn.size() - 1; i++) {
        if (currentColumn[i - 1]->getState() == Crate::CrateState::IDLE &&
            currentColumn[i]->getState() == Crate::CrateState::IDLE &&
            currentColumn[i + 1]->getState() == Crate::CrateState::IDLE) {
          if (currentColumn[i]->getCrateType() ==
                  currentColumn[i - 1]->getCrateType() &&
              currentColumn[i]->getCrateType() ==
                  currentColumn[i + 1]->getCrateType()) {

            scorer->addMergeScore(currentColumn[i]);
            currentColumn[i - 1]->setState(Crate::CrateState::FADINGOUT);
            currentColumn[i]->setState(Crate::CrateState::FADINGOUT);
            currentColumn[i + 1]->setState(Crate::CrateState::FADINGOUT);
            currentColumn[i - 1]->restartClock();
            currentColumn[i]->restartClock();
            currentColumn[i + 1]->restartClock();
            // currentColumn[i]->setMerged();
            // toMerge.push_back(std::make_pair(i,
            // currentColumn[i]->nextCrate()));
            Crate *tempCrate = getCrateFromEnum(currentColumn[i]->nextCrate());
            if (tempCrate != nullptr) {
              tempCrate->setState(Crate::CrateState::FADINGIN);
              tempCrate->restartClock();
              tempCrate->setInitHeight(GameConstants::ROW_Y[i]);
              // currentColumn.insert(currentColumn.begin() + i, tempCrate);
              fadingInCrates.push_back(
                  make_pair(tempCrate, sf::Vector2f(column, i)));
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
      scorer->addMergeScore(crates[column][item.first]);
      destroyCrate(column, item.first + 1);
      destroyCrate(column, item.first);
      destroyCrate(column, item.first - 1);
      currentColumn.insert(currentColumn.begin() + item.first - 1, tempCrate);
    }
  }
}

void Crates::explodeCrate() {
  for (int column = 0; column < GameConstants::CRATE_COLUMNS; column++) {
    for (int row = 0; row < crates[column].size(); row++) {
      Crate *currentCrate = crates[column][row];
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

bool Crates::explodeCrateRange(int line, int _start, int _end) {
  if (line >= 0 && line < GameConstants::CRATE_COLUMNS) {
    int start, end;
    start = std::max(_start, _end);
    end = std::min(_start, _end);
    for (int row = start + 1; row < crates[line].size(); row++) {
      if (crates[line][row]->getState() == Crate::CrateState::IDLE) {
        crates[line][row]->restartClock();
        crates[line][row]->setState(Crate::CrateState::FALLING);
        crates[line][row]->setInitHeight(GameConstants::ROW_Y[row]);
      }
    }
    for (int row = start; row >= end; row--) {
      if (crates[line].size() > row) {
        if (crates[line][row]->getState() == Crate::CrateState::IDLE) {
          if (crates[line][row]->explodable()) {
            crates[line][row]->setState(Crate::CrateState::FADINGOUT);
            crates[line][row]->restartClock();
            scorer->addExplodeScore(crates[line][row]);
          } else {
            crates[line][row]->setState(Crate::CrateState::FALLING);
            crates[line][row]->setInitHeight(GameConstants::ROW_Y[row]);
            crates[line][row]->restartClock();
          }
        }
      }
    }
    return true;
  }
  return false;
}

void Crates::drawCrates(sf::RenderWindow &window) {
  for (std::vector<Crate *> column : crates) {
    for (Crate *crate : column) {
      crate->drawCrate(window);
    }
  }
  for (auto crate : fadingInCrates) {
    crate.first->drawCrate(window);
  }
  if (grabbedCrate != nullptr)
    grabbedCrate->drawCrate(window);
}

float Crates::getTopCrateHeight(int line) {
  if (crates[line].size() == 0)
    return 0;
  return crates[line].back()->getPos().y;
}

float Crates::getNextCrateHeight(int line) {
  if (crates[line].size() == 0)
    return GameConstants::ROW_Y[0];
  return crates[line].back()->getPos().y - GameConstants::CRATE_SIZE.y;
}

Crate *Crates::makeCrate(Crate *crate) {
  Crate *temp(crate);
  return temp;
}

bool Crates::grabCrate(int line) {
  if (crates[line].size() == 0)
    return false;
  grabbedCrate = crates[line].back();
  crates[line].erase(crates[line].end() - 1);
  return true;
}

bool Crates::placeCrate(int line) {
  if (crates[line].size() == GameConstants::CRATES_PER_LINE)
    return false;
  grabbedCrate->setState(Crate::CrateState::FALLING);
  grabbedCrate->restartClock();
  grabbedCrate->setInitHeight(grabbedCrate->getPos().y);
  crates[line].push_back(grabbedCrate);
  grabbedCrate = nullptr;
  return true;
}

bool Crates::setGrabbedCratePos(sf::Vector2f pos) {
  if (grabbedCrate == nullptr)
    return false;
  grabbedCrate->setPosition(pos);
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