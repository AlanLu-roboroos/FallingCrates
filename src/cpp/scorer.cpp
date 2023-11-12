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
  m_score.setPosition(sf::Vector2f(100, 73));
  m_highScore.setPosition(sf::Vector2f(1924 - 100, 73));
}

void Scorer::drawScore(sf::RenderWindow &window) {
  m_score.setString(std::to_string(m_scoreNum));
  m_highScore.setString(std::to_string(m_highScoreNum));

  for (int i = m_scoreMarkers.size() - 1; i >= 0; i--) {
    if (255 - 0.51 * (m_clock.getElapsedTime().asMilliseconds() -
                      m_scoreMarkers[i].second) <=
        0)
      m_scoreMarkers.erase(m_scoreMarkers.begin() + i);
    else {

      m_scoreMarkers[i].first.setFillColor(
          sf::Color(255, 255, 255,
                    255 - 0.51 * (m_clock.getElapsedTime().asMilliseconds() -
                                  m_scoreMarkers[i].second)));
      m_scoreMarkers[i].first.move(
          0, -0.001 * (m_clock.getElapsedTime().asMilliseconds() -
                       m_scoreMarkers[i].second));
      window.draw(m_scoreMarkers[i].first);
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
  sf::Text tempText;
  tempText.setFont(GameConstants::Resources::SCORE_FONT);
  tempText.setCharacterSize(60);
  tempText.setFillColor(sf::Color(255, 255, 255));
  tempText.setString("+" + std::to_string(score_add));
  tempText.setOrigin(
      tempText.getLocalBounds().left + tempText.getLocalBounds().width / 2.0f,
      tempText.getLocalBounds().top + tempText.getLocalBounds().height / 2.0f);
  tempText.setPosition(pos);
  m_scoreMarkers.push_back(
      std::make_pair(tempText, m_clock.getElapsedTime().asMilliseconds()));
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