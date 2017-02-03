//
// Created by Denis Sancov on 13/01/2017.
//

#ifndef PROJECT_HY454_GAMEENGINEINTERFACE_H
#define PROJECT_HY454_GAMEENGINEINTERFACE_H

#include <string>
#include <functional>
#include "../Event.h"
#include "SoundSystemInterface.h"
#include "GraphicsSystemInterface.h"

namespace csd {

    class GameEngineInterface {
    public:

        virtual void initialize() = 0;

        std::shared_ptr<GraphicsSystemInterface> renderingSystem()  const { return _graphicsSystem; }
        std::shared_ptr<SoundSystemInterface>    soundSystem()      const { return _soundSystem; }

        virtual void setCursorHidden(bool hidden) = 0;
        virtual void pollEvent(std::function<void(std::shared_ptr<Event> const eventPtr)> eventLambda) = 0;
        virtual void delay(uint32_t ms) = 0;


        virtual void terminate() = 0;

    protected:
        GameEngineInterface() {};
        GameEngineInterface(GameEngineInterface const &) {};
        void operator=(GameEngineInterface const &) {};

        std::shared_ptr<GraphicsSystemInterface>  _graphicsSystem = nullptr;
        std::shared_ptr<SoundSystemInterface>     _soundSystem = nullptr;
    };
}


#endif //PROJECT_HY454_GAMEENGINEINTERFACE_H
