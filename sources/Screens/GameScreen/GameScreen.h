//
// Created by Denis Sancov on 18/11/2016.
//

#ifndef PROJECT_HY454_GAMESCREEN_H
#define PROJECT_HY454_GAMESCREEN_H

#include <chrono>
#include "../../core/AbstractScreen.h"
#include "../../core/Sprites/TextSprite.h"
#include "BirdSprite.h"
#include "BarrierContainer.h"
#include "../../core/Sprites/InfiniteBackgroundSprite.h"

namespace csd {


    typedef enum _gameScreenState {
        GameScreenStateDefault = 1,
        GameScreenStateGetReady,
        GameScreenStateGameInProgress,
        GameScreenStateGameOver
    } GameScreenState;

    class GameScreen : public AbstractScreen {
    public:
        GameScreen(std::function<void(unsigned int score)> const gameOverCallback);

        void setGameScreenState(GameScreenState const state);
        GameScreenState getState() const;


        void setPause(bool const pause) override;
        void handleEvent(std::shared_ptr<Event> const eventPtr) override;

        void handleGameLoop() override;



        bool allowRenderDuringThePause() override;
    private:
        std::function<void(unsigned int score)> _gameOverCallback = nullptr;

        std::shared_ptr<InfiniteBackgroundSprite> _landSprite, _backgroundSprite;
        std::shared_ptr<ImageSprite> _gameStateSprite, _getReadyBackground;
        std::shared_ptr<BirdSprite>  _birdSprite;

        std::shared_ptr<TextSprite>        _userScoreSprite;
        std::shared_ptr<BarrierContainer>  _barrierContainer;

        GameScreenState _state = GameScreenStateDefault;

        unsigned short _score = 0;
        void updateUserScoreSprite();
    };
}

#endif //PROJECT_HY454_GAMESCREEN_H
