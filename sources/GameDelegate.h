//
// Created by Denis Sancov on 14/01/2017.
//

#ifndef PROJECT_HY454_GAMEDELEGATE_H
#define PROJECT_HY454_GAMEDELEGATE_H

#include "core/Timer.h"
#include "core/ScreenStack.h"
#include "core/GameEngineAbstract/GameEngineInterface.h"

namespace csd {

    const int FPS = 60;
    const int TICKS_PER_FRAME = 1000 / FPS;

    class GameDelegate {
    public:
        static GameDelegate& sharedInstance() {
            static GameDelegate gameDelegate;
            return gameDelegate;
        }

        void init(std::shared_ptr<GameEngineInterface> engine);

        int start();

        std::shared_ptr<GameEngineInterface> getGameEngine() const { return _gameEngine; }
    private:
        GameDelegate() {};
        GameDelegate(GameDelegate const&) { };
        void operator=(GameDelegate const&) { };

        std::shared_ptr<GameEngineInterface> _gameEngine;
        std::unique_ptr<ScreenStack> _screenStack;

        bool _quit = false;

        Timer _fpsTimer;
        Timer _runtimeTimer;

        void presentStartScreen();
        void startNewGame();
        void togglePauseScreen();
        void presentResultScreen(unsigned int score);

        void terminate();
        void clear();
    };
}


#endif //PROJECT_HY454_GAMEDELEGATE_H
