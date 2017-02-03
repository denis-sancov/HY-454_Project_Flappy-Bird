//
// Created by Denis Sancov on 03/01/2017.
//

#ifndef PROJECT_HY454_PAUSESCREEN_H
#define PROJECT_HY454_PAUSESCREEN_H


#include "../../core/AbstractScreen.h"
#include "../../core/Sprites/ImageSprite.h"

namespace csd {
    class PauseScreen : public AbstractScreen {
    public:
        PauseScreen();
        void handleEvent(std::shared_ptr<Event> const eventPtr) override;

        std::function<void(void)> onResumeButtonClickedCallback;
        std::function<void(void)> onMenuButtonClickedCallback;
        std::function<void(void)> onExitButtonClickedCallback;

    private:
        std::shared_ptr<ImageSprite> _resumeButtonSprite, _menuButtonSprite, _exitButtonSprite;
    };
}


#endif //PROJECT_HY454_PAUSESCREEN_H
