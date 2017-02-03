//
// Created by Denis Sancov on 30/12/2016.
//

#ifndef PROJECT_HY454_RESULTSCREEN_H
#define PROJECT_HY454_RESULTSCREEN_H

#include "../../core/AbstractScreen.h"
#include "../../core/Sprites/ImageSprite.h"

namespace csd {

    class ResultScreen : public AbstractScreen {
    public:
        ResultScreen(unsigned int const score);
        void handleEvent(std::shared_ptr<Event> const eventPtr) override;

        std::function<void(void)> onOKButtonClicked;
    private:
        unsigned int const _score = 0;
        std::shared_ptr<ImageSprite> _okButtonSprite;
    };
}


#endif //PROJECT_HY454_RESULTSCREEN_H
