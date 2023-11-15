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
  readHighScore();
}

Scorer::~Scorer() { writeHighScore(); }

void Scorer::reset() { m_scoreNum = 0; }

void Scorer::readHighScore() {
  if (!std::filesystem::exists(GameConstants::Resources::SCORE_FILE_PATH)) {
    scoreFile.open(GameConstants::Resources::SCORE_FILE_PATH,
                   std::ofstream::out | std::ofstream::trunc);
    scoreFile << 0;
    scoreFile.close();
  } else {
    scoreFile.open(GameConstants::Resources::SCORE_FILE_PATH,
                   std::ifstream::in);
    int temp;
    scoreFile >> temp;
    m_highScoreNum = temp;
    scoreFile.close();
  }
}
void Scorer::writeHighScore() {
  scoreFile.open(GameConstants::Resources::SCORE_FILE_PATH,
                 std::ofstream::out | std::ofstream::trunc);
  scoreFile << m_highScoreNum;
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

void Scorer::play() { m_clock.play(); }

void Scorer::pause() { m_clock.pause(); }