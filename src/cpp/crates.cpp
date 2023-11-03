#include "crates.hpp"

Crates::Crates() {
  crates = vector<crate_col>(8);
  grabbedCrate = nullptr;
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

Crate *Crates::popCrate(int line) {
  Crate *temp = crates[line].back();
  crates[line].pop_back();
  return temp;
}

void Crates::destroyCrate(int line, int row) {
  delete crates[line][row];
  crates[line].erase(crates[line].begin() + row);
}

void Crates::update() {
  for (int column = 0; column < crates.size(); column++) {
    for (int row = 0; row < crates[column].size(); row++) {
      Crate *currentCrate = crates[column][row];
      float temp;

      switch (currentCrate->getState()) {
      case Crate::CrateState::SPAWNING:
        currentCrate->setPosition(GameConstants::SPAWN_POS[column]);
        temp = GameConstants::CRATE_GROWTH_SPEED *
               currentCrate->getElapsedTime().asMilliseconds();
        if (temp > GameConstants::CRATE_SIZE.x) {
          temp = GameConstants::CRATE_SIZE.x;
          currentCrate->restartClock();
          currentCrate->setState(Crate::CrateState::FALLING);
          currentCrate->setInitHeight(GameConstants::SPAWN_HEIGHT);
        }
        currentCrate->setSize(sf::Vector2f(temp, temp));
        break;
      case Crate::CrateState::FALLING:
        temp =
            GameConstants::CRATE_FALLING_ACCELERATION *
                std::pow(currentCrate->getElapsedTime().asMilliseconds(), 2) +
            currentCrate->getInitHeight();
        if (temp > GameConstants::ROW_Y[row]) {
          temp = GameConstants::ROW_Y[row];
          currentCrate->restartClock();
          currentCrate->setState(Crate::CrateState::IDLE);
        }
        currentCrate->setPosition(GameConstants::SPAWN_POS[column].x, temp);
        break;
      case Crate::CrateState::IDLE:
        currentCrate->setPosition(sf::Vector2f(GameConstants::COLUMN_X[column],
                                               GameConstants::ROW_Y[row]));
        break;
      default:
        break;
      }
    }
    // Add merge code here
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

            toMerge.push_back(std::make_pair(i, currentColumn[i]->nextCrate()));
          }
        }
      }
    }
    for (auto item : toMerge) {
      Crate *tempCrate = getCrateFromEnum(item.second);
      tempCrate->setState(Crate::CrateState::FALLING);
      tempCrate->restartClock();
      tempCrate->setInitHeight(GameConstants::ROW_Y[item.first]);
      destroyCrate(column, item.first + 1);
      destroyCrate(column, item.first);
      destroyCrate(column, item.first - 1);
      currentColumn.insert(currentColumn.begin() + item.first - 1, tempCrate);
    }
  }
}

void Crates::drawCrates(sf::RenderWindow &window) {
  for (std::vector<Crate *> column : crates) {
    for (Crate *crate : column) {
      crate->drawCrate(window);
    }
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
  default:
    break;
  }
  return tempCrate;
}