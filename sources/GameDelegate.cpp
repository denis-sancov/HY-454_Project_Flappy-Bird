//
// Created by Denis Sancov on 14/01/2017.
//

#include "GameDelegate.h"
#include "core/AnimatorManager.h"
#include "Screens/GameScreen/GameScreen.h"
#include "Screens/StartScreen/StartScreen.h"
#include "Screens/PauseScreen/PauseScreen.h"
#include "Screens/ResultScreen/ResultScreen.h"

using namespace csd;

void GameDelegate::init(std::shared_ptr<GameEngineInterface> engine) {
    if (_gameEngine.get() != nullptr) {
        throw std::invalid_argument("Game engine is already set");
    }
    _gameEngine = engine;

    _gameEngine->initialize();

    std::function<void(unsigned int score)> onGameOverCallback = [this](unsigned int score) {
        this->presentResultScreen(score);
    };
    auto rootScreen = std::shared_ptr<GameScreen>(new GameScreen(onGameOverCallback));
    _screenStack = std::unique_ptr<ScreenStack>(new ScreenStack(rootScreen));

    presentStartScreen();
}

void GameDelegate::presentStartScreen() {
    _gameEngine->setCursorHidden(false);
    auto gameScreen = std::dynamic_pointer_cast<GameScreen>(_screenStack->getScreenAtIndex(0));
    gameScreen->setGameScreenState(GameScreenStateDefault);

    if (_screenStack->getTopScreen() != gameScreen) {
        _screenStack->pop();
    }

    auto startScreen = std::shared_ptr<StartScreen>(new StartScreen());
    startScreen->onStartButtonClickedCallback = [this] {
        this->startNewGame();
    };
    startScreen->onExitButtonClickedCallback = [this] {
        this->terminate();
    };
    _screenStack->pushScreen(startScreen);
}

void GameDelegate::startNewGame() {
    _gameEngine->setCursorHidden(true);
    _screenStack->pop();
    auto gameScreen = std::dynamic_pointer_cast<GameScreen>(_screenStack->getScreenAtIndex(0));
    gameScreen->setGameScreenState(GameScreenStateGetReady);
}

void GameDelegate::togglePauseScreen() {
    auto gameScreen = std::dynamic_pointer_cast<GameScreen>(_screenStack->getScreenAtIndex(0));

    switch (gameScreen->getState()) {
        case GameScreenStateGetReady:
        case GameScreenStateGameOver: {
            this->presentStartScreen();
            break;
        }
        case GameScreenStateGameInProgress: {
            auto tmpScreen = _screenStack->getTopScreen();
            if (dynamic_cast<csd::PauseScreen *>(tmpScreen.get())) {
                _gameEngine->setCursorHidden(true);
                _screenStack->pop();
            } else {
                _gameEngine->setCursorHidden(false);

                auto pauseScreen = std::shared_ptr<PauseScreen>(new PauseScreen());
                pauseScreen->onResumeButtonClickedCallback = [this] {
                    this->togglePauseScreen();
                };
                pauseScreen->onMenuButtonClickedCallback = [this] {
                    this->presentStartScreen();
                };
                pauseScreen->onExitButtonClickedCallback = [this] {
                    this->terminate();
                };
                _screenStack->pushScreen(pauseScreen);
            }
            break;
        }
        default: break;
    }
}

void GameDelegate::presentResultScreen(unsigned int score) {
    _gameEngine->setCursorHidden(false);
    auto resultScreen = std::shared_ptr<ResultScreen>(new ResultScreen(score));
    resultScreen->onOKButtonClicked = [this] {
        this->startNewGame();
    };
    _screenStack->pushScreen(resultScreen);
}

int GameDelegate::start() {
    if (_gameEngine.get() == nullptr) {
        throw std::invalid_argument("Game engine is not set");
    }

    if (_screenStack.get() == nullptr) {
        throw std::invalid_argument("Screen stack has to be initialized");
    }

    uint32_t frameTicks = 0;

    _runtimeTimer.start();

    AnimatorManager &animator = AnimatorManager::shared();

    while (!this->_quit) {
        _fpsTimer.start();

        _gameEngine->pollEvent([this](std::shared_ptr<csd::Event> eventPtr) {
            if (dynamic_cast<csd::TerminateGameEvent *>(eventPtr.get())) {
                return this->terminate();
            }

            if (dynamic_cast<csd::KeyboardEvent *>(eventPtr.get())) {
                auto keyboardEvent = std::dynamic_pointer_cast<KeyboardEvent>(eventPtr);
                if (keyboardEvent->keyCode() == 41 && keyboardEvent->getEvent()== Event::PressedDown) {
                    togglePauseScreen();
                    return;
                }
            }
            _screenStack->handleEvent(eventPtr);
        });

        animator.progress(_runtimeTimer.getTicksInMS());
        _gameEngine->renderingSystem()->clear();

        _screenStack->handleGameLoop();

        _gameEngine->renderingSystem()->presentRenderedDataOnScreen();

        _gameEngine->renderingSystem()->releaseUnusedBitmaps();

        frameTicks = _fpsTimer.getTicksInMS();
        if(frameTicks < TICKS_PER_FRAME) {
            _gameEngine->delay(TICKS_PER_FRAME - frameTicks);
        }
    }

    clear();

    return 0;
}

void GameDelegate::terminate() {
    _quit = true;
}

void GameDelegate::clear() {
    _gameEngine->terminate();
}