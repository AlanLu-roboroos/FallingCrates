#include "scorer.hpp"

Scorer::Scorer() {
  m_scoreNum = 0;
  m_highScoreNum = 0;

  m_score.setFont(GameConstants::Resources::SCORE_FONT);
  m_highScore.setFont(GameConstants::Resources::SCORE_FONT);

  m_score.setCharacterSize(80);
  m_score.setFillColor(sf::Color(0, 0, 0));

  m_highScore.setCharacterSize(80);
  m_highScore.setFillColor(sf::Color(255, 0, 0));

  m_score.setString(std::to_string(m_scoreNum));
  m_highScore.setString(std::to_string(m_highScoreNum));

  m_score.setOrigin(m_score.getLocalBounds().left,
                    m_score.getLocalBounds().top +
                        m_score.getLocalBounds().height / 2.0f);
  m_highScore.setOrigin(m_highScore.getLocalBounds().left +
                            m_highScore.getLocalBounds().width,
                        m_highScore.getLocalBounds().top +
                            m_highScore.getLocalBounds().height / 2.0f);
  m_score.setPosition(sf::Vector2f(300, 73));
  m_highScore.setPosition(sf::Vector2f(GameConstants::WINDOW_WIDTH - 100, 73));

  key.push_back(5);
  key.push_back(4);
  key.push_back(3);
  key.push_back(1);

  readHighScore();
}

Scorer::~Scorer() { writeHighScore(); }

void Scorer::reset() { m_scoreNum = 0; }

void Scorer::readHighScore() {
  if (!std::filesystem::exists(GameConstants::Resources::SCORE_FILE_PATH)) {
    scoreFile.open(GameConstants::Resources::SCORE_FILE_PATH,
                   std::ofstream::out | std::ofstream::trunc);
    scoreFile << encrypt("0", key);
    scoreFile.close();
  } else {
    scoreFile.open(GameConstants::Resources::SCORE_FILE_PATH,
                   std::ifstream::in);
    std::string temp;
    scoreFile >> temp;
    m_highScoreNum = std::stoi(decrypt(temp, key));
    scoreFile.close();
  }
}
void Scorer::writeHighScore() {
  scoreFile.open(GameConstants::Resources::SCORE_FILE_PATH,
                 std::ofstream::out | std::ofstream::trunc);
  scoreFile << encrypt(std::to_string(m_highScoreNum), key);
  scoreFile.close();
}

void Scorer::drawScore(sf::RenderWindow &window) {
  m_score.setString(std::to_string(m_scoreNum));
  m_highScore.setString(std::to_string(m_highScoreNum));

  for (int i = m_scoreMarkers.size() - 1; i >= 0; i--) {
    if (255 - 0.51 * (m_clock.getElapsedTime().asMilliseconds() -
                      m_scoreMarkers[i].initTime.asMilliseconds()) <=
        0)
      m_scoreMarkers.erase(m_scoreMarkers.begin() + i);
    else {

      m_scoreMarkers[i].text.setFillColor(sf::Color(
          255, 255, 255,
          255 - 0.51 * (m_clock.getElapsedTime().asMilliseconds() -
                        m_scoreMarkers[i].initTime.asMilliseconds())));
      m_scoreMarkers[i].text.setPosition(
          m_scoreMarkers[i].initPos.x,
          m_scoreMarkers[i].initPos.y -
              0.1 * (m_clock.getElapsedTime().asMilliseconds() -
                     m_scoreMarkers[i].initTime.asMilliseconds()));
      window.draw(m_scoreMarkers[i].text);
    }
  }
  m_highScore.setOrigin(m_highScore.getLocalBounds().left +
                            m_highScore.getLocalBounds().width,
                        m_highScore.getLocalBounds().top +
                            m_highScore.getLocalBounds().height / 2.0f);
  window.draw(m_score);
  window.draw(m_highScore);
}

void Scorer::addScore(int score_add, sf::Vector2f pos) {
  m_scoreNum += score_add;
  m_highScoreNum = std::max(m_highScoreNum, m_scoreNum);
  ScoreMarker temp;
  temp.text.setFont(GameConstants::Resources::SCORE_FONT);
  temp.text.setCharacterSize(60);
  temp.text.setFillColor(sf::Color(255, 255, 255));
  temp.text.setString("+" + std::to_string(score_add));
  temp.text.setOrigin(temp.text.getLocalBounds().left +
                          temp.text.getLocalBounds().width / 2.0f,
                      temp.text.getLocalBounds().top +
                          temp.text.getLocalBounds().height / 2.0f);
  temp.text.setPosition(pos);
  temp.initTime = m_clock.getElapsedTime();
  temp.initPos = pos;
  m_scoreMarkers.push_back(temp);
}

void Scorer::addMergeScore(Crate *crate) {
  addScore(GameConstants::CRATE_MERGE_SCORE[crate->getCrateType()],
           crate->getPos());
}

void Scorer::addExplodeScore(Crate *crate) {
  addScore(GameConstants::CRATE_EXPLODE_SCORE[crate->getCrateType()],
           crate->getPos());
}

int Scorer::gcd(int a, int b) {
  // Function to return the Greatest Common Divisor of a and b.
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

void Scorer::extendedGCD(int a, int b, int &x, int &y) {
  // Extended Euclidean Algorithm.
  if (a == 0) {
    x = 0;
    y = 1;
    return;
  }

  int x1, y1;
  extendedGCD(b % a, a, x1, y1);

  x = y1 - (b / a) * x1;
  y = x1;
}

int Scorer::modInverse(int a, int m) {
  // Function to find the modular inverse of a under modulo m.
  int x, y;
  extendedGCD(a, m, x, y);
  if (gcd(a, m) != 1) {
    // Modular inverse does not exist if a and m are not coprime.
    return -1;
  } else {
    // Handling negative values.
    return (x % m + m) % m;
  }
}

int Scorer::mod(int a, int b) { return ((a % b) + b) % b; }

int Scorer::c2i(char c) { return mod(static_cast<int>(c) - 34, 89); }
char Scorer::i2c(int i) { return static_cast<char>(mod(i, 89) + 34); }

std::string Scorer::encrypt(std::string raw, std::vector<int> key) {
  std::vector<int> vec;
  if (raw.size() % 2 != 0) {
    raw.insert(0, "0");
  }

  for (int i = 0; i < raw.size() / 2; i++) {
    int a = c2i(raw[2 * i]), b = c2i(raw[2 * i + 1]);
    vec.push_back(mod(key[0] * a + key[1] * b, 89));
    vec.push_back(mod(key[2] * a + key[3] * b, 89));
  }

  std::string out;
  for (int i : vec) {
    out += i2c(i);
  }

  return out;
}

std::string Scorer::decrypt(std::string raw, std::vector<int> key) {
  int inv = modInverse(key[0] * key[3] - key[1] * key[2], 89);
  std::vector<int> newKey;

  newKey.push_back(mod(key[3] * inv, 89));
  newKey.push_back(mod(-key[1] * inv, 89));
  newKey.push_back(mod(-key[2] * inv, 89));
  newKey.push_back(mod(key[0] * inv, 89));

  std::vector<int> vec;
  for (int i = 0; i < raw.size() / 2; i++) {
    int a = c2i(raw[2 * i]), b = c2i(raw[2 * i + 1]);
    vec.push_back(mod(newKey[0] * a + newKey[1] * b, 89));
    vec.push_back(mod(newKey[2] * a + newKey[3] * b, 89));
  }

  std::string out;
  for (int i : vec) {
    out += i2c(i);
  }

  return out;
}

void Scorer::play() { m_clock.play(); }

void Scorer::pause() { m_clock.pause(); }