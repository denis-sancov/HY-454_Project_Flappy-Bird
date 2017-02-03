//
// Created by Denis Sancov on 18/11/2016.
//

#include "GameScreen.h"
#include "../../core/GameSettings.h"
#include "../../core/SoundManager.h"

using namespace csd;

GameScreen::GameScreen(std::function<void(unsigned int score)> const gameOverCallback) : AbstractScreen() {
    _gameOverCallback = gameOverCallback;

    auto layer = getLayer();
    Size layerSize = layer->getSize();



    _gameStateSprite = std::shared_ptr<ImageSprite>(new ImageSprite("Resources/Bitmaps/IconPauseGame.bmp"));
    _gameStateSprite->setHidden(true);
    _gameStateSprite->setPosition((Point){ 20, 40 });
    _gameStateSprite->setZIndex(10);
    layer->addSublayer(_gameStateSprite);



    GameSettings& settings = GameSettings::sharedInstance();

    /*
        *      Land
    */

    Point delta = Point {-1, 0};
    int tmpDelay = settings.moveLandAnimationDelay;

    _landSprite = std::shared_ptr<InfiniteBackgroundSprite>(new InfiniteBackgroundSprite("Resources/Bitmaps/Land.bmp", delta, tmpDelay));
    _landSprite->setPosition(Point {
            0, layerSize.height - _landSprite->getSize().height
    });
    _landSprite->setSize(Size {
            layerSize.width, _landSprite->getSize().height
    });
    _landSprite->setZIndex(10);

    layer->addSublayer(_landSprite);



    /*
     * sky background
     */

    tmpDelay = settings.moveBackgroundAnimationDelay;
    _backgroundSprite = std::shared_ptr<InfiniteBackgroundSprite>(new InfiniteBackgroundSprite("Resources/Bitmaps/Background.bmp", delta, tmpDelay));
    _backgroundSprite->setPosition(PointZero());
    _backgroundSprite->setSize((Size){
            layerSize.width,
            layerSize.height - _landSprite->getSize().height
    });
    layer->addSublayer(_backgroundSprite);



    /*
     *  Get Ready popup
     */

    _getReadyBackground = std::shared_ptr<ImageSprite>(new ImageSprite("Resources/Bitmaps/GetReadyBackground.bmp"));
    _getReadyBackground->setPosition((Point) {
            (layerSize.width - _getReadyBackground->getSize().width) / 2,
            (_backgroundSprite->getSize().height - _getReadyBackground->getSize().height) / 2
    });
    _getReadyBackground->setZIndex(10);
    _getReadyBackground->setHidden(true);
    layer->addSublayer(_getReadyBackground);


    /*
     *      Bird Sprite
     */
    _birdSprite = std::shared_ptr<BirdSprite>(new BirdSprite());
    _birdSprite->setZIndex(9);
    _birdSprite->setHidden(true);
    layer->addSublayer(_birdSprite);

    std::vector<Rect> collisionBoxes;
    collisionBoxes.push_back(Rect{
            _birdSprite->getPosition(), _birdSprite->getFrameSize()
    });

    _birdSprite->setCollisionBoxes(collisionBoxes);


    /*
     *  User Score
     */

    _userScoreSprite = std::shared_ptr<TextSprite>(new TextSprite("0"));
    _userScoreSprite->setZIndex(15);
    _userScoreSprite->setFontSize(50);
    _userScoreSprite->setTextColor(Color::White());
    _userScoreSprite->setHidden(true);
    layer->addSublayer(_userScoreSprite);


    auto barrierPassLambda = [this](unsigned int passBarrierPoints) {
        SoundManager::sharedInstance().playSound(SoundManager::SoundPoint);
        _score += passBarrierPoints;
        updateUserScoreSprite();
    };

    _barrierContainer = std::shared_ptr<BarrierContainer>(new BarrierContainer(barrierPassLambda));
    _barrierContainer->setZIndex(8);
    _barrierContainer->setSize(Size {
            layerSize.width,
            layerSize.height - _landSprite->getSize().height
    });
    layer->addSublayer(_barrierContainer);

    this->setGameScreenState(GameScreenStateDefault);
}

GameScreenState GameScreen::getState() const {
    return _state;
}

void GameScreen::setGameScreenState(GameScreenState const state) {
    switch (state) {
        case GameScreenStateDefault: {
            _getReadyBackground->setHidden(true);
            _birdSprite->setHidden(true);
            _gameStateSprite->setHidden(true);
            _userScoreSprite->setHidden(true);
            _landSprite->setPaused(false);
            _backgroundSprite->setPaused(false);

            _barrierContainer->setPaused(true);
            _barrierContainer->reset();
            break;
        }
        case GameScreenStateGetReady: {
            SoundManager::sharedInstance().playSound(SoundManager::SoundWooshing);
            _score = 0;
            updateUserScoreSprite();

            _userScoreSprite->setHidden(false);
            _gameStateSprite->setHidden(false);
            _getReadyBackground->setHidden(false);

            _birdSprite->setVelocity(Point{0, 0});
            _birdSprite->setAngle(0.f);
            _birdSprite->setState(BirdStateReady);
            _birdSprite->setPosition(Point {
                    160, (_backgroundSprite->getSize().height - _birdSprite->getSize().height) / 2
            });
            _birdSprite->setHidden(false);

            _barrierContainer->reset();
            break;
        }
        case GameScreenStateGameInProgress: {
            _birdSprite->setState(BirdStateCanFly);
            _landSprite->setPaused(false);
            _backgroundSprite->setPaused(false);
            _barrierContainer->setPaused(false);
            break;
        }
        case GameScreenStateGameOver: {
            SoundManager::sharedInstance().playSound(SoundManager::SoundHit);
            _birdSprite->setState(BirdStateDead);
            _landSprite->setPaused(true);
            _backgroundSprite->setPaused(true);
            _barrierContainer->setPaused(true);
            _gameOverCallback(_score);
            break;
        }
    }

    _state = state;
}

void GameScreen::updateUserScoreSprite() {
    _userScoreSprite->setText(std::to_string(_score));
    _userScoreSprite->setPosition(Point{
            (getLayer()->getSize().width - _userScoreSprite->getSize().width) / 2,
            _gameStateSprite->getPosition().y
    });
}

void GameScreen::setPause(bool pause) {
    AbstractScreen::setPause(pause);
    if (_state != GameScreenStateGameInProgress) {
        return;
    }

    _landSprite->setPaused(pause);
    _backgroundSprite->setPaused(pause);
    _birdSprite->setState((pause == true) ? BirdStateReady: BirdStateCanFly);
    _barrierContainer->setPaused(pause);
    _gameStateSprite->setBitmapFromFile((pause == true) ? "Resources/Bitmaps/IconResumeGame.bmp"
                                                        : "Resources/Bitmaps/IconPauseGame.bmp");
}

void GameScreen::handleEvent(std::shared_ptr<Event> const eventPtr) {
    bool canHandleEvent = false;

    if (dynamic_cast<csd::MouseEvent *>(eventPtr.get())) {
        auto mouseEvent = std::dynamic_pointer_cast<MouseEvent>(eventPtr);
        canHandleEvent = (mouseEvent->getEvent() == Event::PressedDown);

    } else if (dynamic_cast<csd::KeyboardEvent *>(eventPtr.get())) {
        auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(eventPtr);
        canHandleEvent = (keyboardEvent->getEvent() == Event::PressedDown);
    }

    if (!canHandleEvent) {
        return;
    }

    switch (_state) {
        case GameScreenStateGetReady: {
            _getReadyBackground->setHidden(true);
            setGameScreenState(GameScreenStateGameInProgress);
            break;
        }
        case GameScreenStateGameInProgress: {
            if (_birdSprite->getState() != BirdStateCanFly) return;

            SoundManager::sharedInstance().playSound(SoundManager::SoundWing);
            _birdSprite->fly();
            break;
        }
        default: {
            break;
        }
    }
}

void GameScreen::handleGameLoop() {
    AbstractScreen::handleGameLoop();
    if (_state != GameScreenStateGameInProgress) return;

    if (_birdSprite->boundingBoxIntersects(_landSprite)) {
        Point position = _birdSprite->getPosition();
        position.y = _landSprite->getPosition().y - _birdSprite->getFrameSize().height;
        _birdSprite->setVelocity(PointZero());
        _birdSprite->setPosition(position);
        setGameScreenState(GameScreenStateGameOver);
        return;
    }

    if (_birdSprite->getState() != BirdStateFallingDown) {
        if (_barrierContainer->intersectsLayer(_birdSprite)) {
            _birdSprite->setState(BirdStateFallingDown);

            SoundManager::sharedInstance().playSound(SoundManager::SoundHit);
            _landSprite->setPaused(true);
            _backgroundSprite->setPaused(true);
            _barrierContainer->setPaused(true);
            SoundManager::sharedInstance().playSound(SoundManager::SoundDie);
        }
    }

}

bool GameScreen::allowRenderDuringThePause() {
    return true;
}