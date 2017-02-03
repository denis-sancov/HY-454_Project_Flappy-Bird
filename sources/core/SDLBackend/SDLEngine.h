//
// Created by Denis Sancov on 14/11/2016.
//

#ifndef PROJECT_HY454_SDLENGINE_H
#define PROJECT_HY454_SDLENGINE_H

#include "../GameEngineAbstract/GameEngineInterface.h"

namespace csd {
    class SDLEngine : public GameEngineInterface {
    public:
        void initialize() override;

        void setCursorHidden(bool hidden) override;

        void pollEvent(std::function<void(std::shared_ptr<Event> const eventPtr)> eventLambda) override;

        void delay(uint32_t ms) override;

        void terminate() override;
    };
}

#endif //PROJECT_HY454_SDLENGINE_H
