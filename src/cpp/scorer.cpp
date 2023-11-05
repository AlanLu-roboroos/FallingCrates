#include "scorer.hpp"

Scorer::Scorer() {
  scoreNum = 0;
  highScoreNum = 0;

  score.setFont(GameConstants::Resources::SCORE_FONT);
  highScore.setFont(GameConstants::Resources::SCORE_FONT);

  score.setCharacterSize(80);
  score.setFillColor(sf::Color(0, 0, 0));

  highScore.setCharacterSize(80);
  highScore.setFillColor(sf::Color(255, 0, 0));

  score.setString(std::to_string(scoreNum));
  highScore.setString(std::to_string(highScoreNum));

  score.setOrigin(score.getLocalBounds().left,
                  score.getLocalBounds().top +
                      score.getLocalBounds().height / 2.0f);
  highScore.setOrigin(highScore.getLocalBounds().left +
                          highScore.getLocalBounds().width,
                      highScore.getLocalBounds().top +
                          highScore.getLocalBounds().height / 2.0f);
  score.setPosition(sf::Vector2f(100, 73));
  highScore.setPosition(sf::Vector2f(1924 - 100, 73));
}

void Scorer::drawScore(sf::RenderWindow &window) {
  score.setString(std::to_string(scoreNum));
  highScore.setString(std::to_string(highScoreNum));

  for (int i = scoreMarkers.size() - 1; i >= 0; i--) {
    if (255 - 0.51 * (clock.getElapsedTime().asMilliseconds() -
                      scoreMarkers[i].second) <=
        0)
      scoreMarkers.erase(scoreMarkers.begin() + i);
    else {

      scoreMarkers[i].first.setFillColor(
          sf::Color(255, 255, 255,
                    255 - 0.51 * (clock.getElapsedTime().asMilliseconds() -
                                  scoreMarkers[i].second)));
      scoreMarkers[i].first.move(
          0, -0.001 * (clock.getElapsedTime().asMilliseconds() -
                       scoreMarkers[i].second));
      window.draw(scoreMarkers[i].first);
    }
  }
  highScore.setOrigin(highScore.getLocalBounds().left +
                          highScore.getLocalBounds().width,
                      highScore.getLocalBounds().top +
                          highScore.getLocalBounds().height / 2.0f);
  window.draw(score);
  window.draw(highScore);
}

void Scorer::addScore(int score_add, sf::Vector2f pos) {
  scoreNum += score_add;
  highScoreNum = std::max(highScoreNum, scoreNum);
  sf::Text tempText;
  tempText.setFont(GameConstants::Resources::SCORE_FONT);
  tempText.setCharacterSize(60);
  tempText.setFillColor(sf::Color(255, 255, 255));
  tempText.setString("+" + std::to_string(score_add));
  tempText.setOrigin(
      tempText.getLocalBounds().left + tempText.getLocalBounds().width / 2.0f,
      tempText.getLocalBounds().top + tempText.getLocalBounds().height / 2.0f);
  tempText.setPosition(pos);
  scoreMarkers.push_back(
      std::make_pair(tempText, clock.getElapsedTime().asMilliseconds()));
}

void Scorer::addMergeScore(Crate *crate) {
  addScore(GameConstants::CRATE_MERGE_SCORE[crate->getCrateType()],
           crate->getPos());
}