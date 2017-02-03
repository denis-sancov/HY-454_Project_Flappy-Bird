//
// Created by Denis Sancov on 30/12/2016.
//

#ifndef PROJECT_HY454_SCREENSTACK_H
#define PROJECT_HY454_SCREENSTACK_H

#include "AbstractScreen.h"

namespace csd {

    class ScreenStack : public AbstractScreen {
    public:
        ScreenStack(std::shared_ptr<AbstractScreen> const rootScreen);

        void pushScreen(std::shared_ptr<AbstractScreen> const screen);
        void pop();

        std::shared_ptr<AbstractScreen> getTopScreen() const;
        std::shared_ptr<AbstractScreen> getScreenAtIndex(unsigned int index) const;

        void handleEvent(std::shared_ptr<Event> const eventPtr) override;
        void handleGameLoop() override;
    private:
        std::vector<std::shared_ptr<AbstractScreen>> _container;
    };
}

#endif //PROJECT_HY454_SCREENSTACK_H
