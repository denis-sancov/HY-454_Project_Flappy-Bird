//
// Created by Denis Sancov on 30/12/2016.
//

#ifndef PROJECT_HY454_STARTSCREEN_H
#define PROJECT_HY454_STARTSCREEN_H


#include "../../core/AbstractScreen.h"
#include "../../core/Sprites/ImageSprite.h"

namespace csd {
    class StartScreen : public AbstractScreen {
    public:
        StartScreen();

        void handleEvent(std::shared_ptr<Event> const eventPtr) override;

        std::function<void(void)> onStartButtonClickedCallback;
        std::function<void(void)> onExitButtonClickedCallback;
    private:

        std::shared_ptr<ImageSprite> _buttonSprite, _exitButtonSprite;
    };
}



#endif //PROJECT_HY454_STARTSCREEN_H
