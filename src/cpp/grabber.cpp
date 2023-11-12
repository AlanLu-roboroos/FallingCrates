#include "grabber.hpp"

Grabber::Grabber(Crates *__crates) {
  m_column = 3.5;

  m_crates = __crates;

  m_state = GrabberState::STARTING;
  m_nextState = GrabberState::STARTING;

  m_clock = Clock();
  m_lastTime = m_clock.getElapsedTime();

  m_grabHori = sf::Sprite();
  m_grabHori.setTexture(GameConstants::Resources::GRABBER_HORI);
  m_grabHori.setScale(
      GameConstants::CRATE_SIZE.x / m_grabHori.getLocalBounds().width,
      GameConstants::CRATE_SIZE.y / m_grabHori.getLocalBounds().height);
  m_grabHori.setOrigin(sf::Vector2f(8, 12));

  m_grabLeft = sf::Sprite();
  m_grabLeft.setTexture(GameConstants::Resources::GRABBER_LEFT);
  m_grabLeft.setScale(
      GameConstants::CRATE_SIZE.x / m_grabLeft.getLocalBounds().width,
      GameConstants::CRATE_SIZE.y / m_grabLeft.getLocalBounds().height);
  m_grabLeft.setOrigin(sf::Vector2f(24, 14));

  m_grabRight = sf::Sprite();
  m_grabRight.setTexture(GameConstants::Resources::GRABBER_RIGHT);
  m_grabRight.setScale(
      GameConstants::CRATE_SIZE.x / m_grabRight.getLocalBounds().width,
      GameConstants::CRATE_SIZE.y / m_grabRight.getLocalBounds().height);
  m_grabRight.setOrigin(sf::Vector2f(-8, 14));

  m_grabVert = sf::Sprite();
  m_grabVert.setTexture(GameConstants::Resources::GRABBER_VERT);
  m_grabVert.setScale(
      GameConstants::CRATE_SIZE.x / m_grabVert.getLocalBounds().width,
      GameConstants::CRATE_SIZE.y / m_grabVert.getLocalBounds().height);
  m_grabVert.setOrigin(sf::Vector2f(8, 0));

  // _centreDot.setFillColor(sf::Color(255, 0, 0));
  // _centreDot.setRadius(5);

  // _vertBoundingBox.setFillColor(sf::Color(0, 255, 0, 100));
  // _vertBoundingBox.setSize(sf::Vector2f(grabVert.getGlobalBounds().width,
  // grabVert.getGlobalBounds().height));
  setPosition(sf::Vector2f(-5000, -5000));
}

void Grabber::setPosition(sf::Vector2f pos) {
  m_grabHori.setPosition(pos);
  m_grabLeft.setPosition(pos);
  m_grabRight.setPosition(pos);
  m_grabVert.setPosition(sf::Vector2f(pos.x, GameConstants::BORDER_HEIGHT +
                                                 GameConstants::BORDER_WIDTH));
  // grabVert.move(sf::Vector2f(0, -100));

  m_grabVert.setScale(GameConstants::CRATE_SIZE.x /
                          m_grabVert.getLocalBounds().width,
                      (pos.y - 98 - GameConstants::BORDER_HEIGHT) /
                          m_grabVert.getLocalBounds().height);
  // _vertBoundingBox.setOrigin(sf::Vector2f(_vertBoundingBox.getGlobalBounds().width
  // / 2, _vertBoundingBox.getGlobalBounds().height / 2));
  // _vertBoundingBox.setPosition(pos);

  // _centreDot.setPosition(grabVert.getPosition());
}

void Grabber::setPosition(int x, int y) { setPosition(sf::Vector2f(x, y)); }

void Grabber::move(sf::Vector2f delta) {
  m_grabHori.move(delta);
  m_grabLeft.move(delta);
  m_grabRight.move(delta);
  m_grabVert.move(sf::Vector2f(delta.x, 0));
  // grabVert.move(sf::Vector2f(0, -100));

  m_grabVert.setScale(
      GameConstants::CRATE_SIZE.x / m_grabVert.getLocalBounds().width,
      (m_grabHori.getPosition().y - 98 - GameConstants::BORDER_HEIGHT) /
          m_grabVert.getLocalBounds().height);
  // _vertBoundingBox.setOrigin(sf::Vector2f(_vertBoundingBox.getGlobalBounds().width
  // / 2, _vertBoundingBox.getGlobalBounds().height / 2));
  // _vertBoundingBox.setPosition(pos);

  // _centreDot.setPosition(grabVert.getPosition());
}

void Grabber::move(int x, int y) { move(sf::Vector2f(x, y)); }

void Grabber::openGripper() {
  m_grabLeft.setOrigin(sf::Vector2f(26, 14));
  m_grabRight.setOrigin(sf::Vector2f(-10, 14));
  m_grabHori.setScale(
      (GameConstants::CRATE_SIZE.x + 4 * m_grabHori.getScale().x) /
          m_grabVert.getLocalBounds().width,
      (GameConstants::CRATE_SIZE.y) / m_grabVert.getLocalBounds().height);
}

sf::Vector2f Grabber::getPosition() { return m_grabHori.getPosition(); }

void Grabber::closeGripper() {
  m_grabLeft.setOrigin(sf::Vector2f(24, 14));
  m_grabRight.setOrigin(sf::Vector2f(-8, 14));
  m_grabHori.setScale(
      (GameConstants::CRATE_SIZE.x) / m_grabVert.getLocalBounds().width,
      (GameConstants::CRATE_SIZE.y) / m_grabVert.getLocalBounds().height);
}

void Grabber::goTo(int _column) {
  switch (m_state) {
  case GrabberState::STARTING:
  case GrabberState::EMPTY:
    if (m_crates->isLineGrabbable(_column))
      m_nextState = GrabberState::GRABBING;
    else
      m_nextState = GrabberState::EMPTY;
    if (m_column == _column)
      m_state = m_nextState;
    else if (_column < m_column) {
      m_state = GrabberState::SLIDINGLEFT;
    } else if (_column > m_column)
      m_state = GrabberState::SLIDINGRIGHT;
    m_column = _column;
    break;
  case GrabberState::FULL:
    if (m_crates->linePlacable(_column))
      m_nextState = GrabberState::PLACING;
    else
      m_nextState = GrabberState::FULL;
    if (m_column == _column)
      m_state = m_nextState;
    else if (_column < m_column)
      m_state = GrabberState::SLIDINGLEFT;
    else if (_column > m_column)
      m_state = GrabberState::SLIDINGRIGHT;
    m_column = _column;
    break;
  default:
    break;
  }
}

void Grabber::queueGoTo(int line) { m_gotoQueue.push_back(line); }

void Grabber::drawGrabber(sf::RenderWindow &window) {
  window.draw(m_grabHori);
  window.draw(m_grabLeft);
  window.draw(m_grabRight);
  window.draw(m_grabVert);
  // window.draw(_vertBoundingBox);
  // window.draw(_centreDot);
  // std::cout
  //     << grabVert.getGlobalBounds().width << ", " <<
  //     grabVert.getGlobalBounds().height << std::endl;
}

void Grabber::update() {
  if (m_gotoQueue.size() != 0 &&
      (m_state == GrabberState::EMPTY || m_state == GrabberState::FULL ||
       m_state == GrabberState::STARTING)) {
    goTo(m_gotoQueue.front());
    m_gotoQueue.erase(m_gotoQueue.begin());
  }
  switch (m_state) {
  case GrabberState::STARTING:
    openGripper();
    setPosition(GameConstants::GRABBER_START_POS);
    break;
  case GrabberState::EMPTY:
    setPosition(GameConstants::COLUMN_X[m_column],
                GameConstants::GRABBER_START_POS.y);
    openGripper();
    break;
  case GrabberState::FULL:
    setPosition(GameConstants::COLUMN_X[m_column],
                GameConstants::GRABBER_START_POS.y);
    m_crates->setGrabbedCratePos(getPosition());
    closeGripper();
    break;
  case GrabberState::SLIDINGLEFT:
    move(-(GameConstants::GRABBER_HORIZONTAL_SPEED *
           (m_clock.getElapsedTime().asMilliseconds() -
            m_lastTime.asMilliseconds())),
         0);
    if (getPosition().x < GameConstants::PLATFORM_POS[m_column].x) {
      setPosition(GameConstants::SPAWN_POS[m_column].x,
                  GameConstants::GRABBER_START_POS.y);
      m_state = m_nextState;
    }
    m_crates->setGrabbedCratePos(getPosition());
    break;
  case GrabberState::SLIDINGRIGHT:
    move((GameConstants::GRABBER_HORIZONTAL_SPEED *
          (m_clock.getElapsedTime().asMilliseconds() -
           m_lastTime.asMilliseconds())),
         0);
    if (getPosition().x > GameConstants::PLATFORM_POS[m_column].x) {
      setPosition(GameConstants::SPAWN_POS[m_column].x,
                  GameConstants::GRABBER_START_POS.y);
      m_state = m_nextState;
    }
    m_crates->setGrabbedCratePos(getPosition());
    break;
  case GrabberState::GRABBING:
    openGripper();
    move(0, (m_clock.getElapsedTime().asMilliseconds() -
             m_lastTime.asMilliseconds()) *
                GameConstants::GRABBER_VERTICAL_SPEED);
    if (m_grabHori.getPosition().y > m_crates->getTopCrateHeight(m_column)) {
      setPosition(GameConstants::COLUMN_X[m_column],
                  m_crates->getTopCrateHeight(m_column));
      if (m_crates->grabCrate(m_column))
        m_state = GrabberState::LIFTINGCRATE;
      else
        m_state = GrabberState::RETURNING;
    }
    break;
  case GrabberState::PLACING:
    closeGripper();
    move(0, (m_clock.getElapsedTime().asMilliseconds() -
             m_lastTime.asMilliseconds()) *
                GameConstants::GRABBER_VERTICAL_SPEED);
    if (m_grabHori.getPosition().y > m_crates->getNextCrateHeight(m_column)) {
      setPosition(GameConstants::COLUMN_X[m_column],
                  m_crates->getNextCrateHeight(m_column));
      m_crates->setGrabbedCratePos(
          sf::Vector2f(GameConstants::COLUMN_X[m_column],
                       m_crates->getNextCrateHeight(m_column)));
      if (m_crates->placeCrate(m_column)) {
        m_state = GrabberState::RETURNING;
      } else
        m_state = GrabberState::LIFTINGCRATE;
    }
    m_crates->setGrabbedCratePos(getPosition());
    break;
  case GrabberState::LIFTINGCRATE:
    closeGripper();
    move(0, -(m_clock.getElapsedTime().asMilliseconds() -
              m_lastTime.asMilliseconds()) *
                GameConstants::GRABBER_VERTICAL_SPEED);
    if (m_grabHori.getPosition().y < GameConstants::GRABBER_START_POS.y) {
      setPosition(GameConstants::COLUMN_X[m_column],
                  GameConstants::GRABBER_START_POS.y);
      m_state = GrabberState::FULL;
    }
    m_crates->setGrabbedCratePos(getPosition());
    break;
  case GrabberState::RETURNING:
    openGripper();
    move(0, -(m_clock.getElapsedTime().asMilliseconds() -
              m_lastTime.asMilliseconds()) *
                GameConstants::GRABBER_VERTICAL_SPEED);
    if (m_grabHori.getPosition().y < GameConstants::GRABBER_START_POS.y) {
      setPosition(GameConstants::COLUMN_X[m_column],
                  GameConstants::GRABBER_START_POS.y);
      m_state = GrabberState::EMPTY;
    }
    break;
  default:
    break;
  }
  m_lastTime = m_clock.getElapsedTime();
}

int Grabber::getColumn() { return std::abs(m_column); }
bool Grabber::isActive() {
  switch (m_state) {
  case GrabberState::GRABBING:
  case GrabberState::PLACING:
  case GrabberState::LIFTINGCRATE:
  case GrabberState::RETURNING:
    return true;
  default:
    return false;
  }
}

void Grabber::setClockFactor(float _factor) { m_clock.setFactor(_factor); }