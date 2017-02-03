//
// Created by Denis Sancov on 14/11/2016.
//

#ifndef PROJECT_HY454_ABSTRACTSCREEN_H
#define PROJECT_HY454_ABSTRACTSCREEN_H

#include "Event.h"
#include "Sprites/Layer.h"

namespace csd {
    class AbstractScreen : public EventHandler {
    public:
        virtual void setPause(bool pause);
        bool isPaused() const;

        const std::shared_ptr<Layer> getLayer();

        virtual void handleEvent(std::shared_ptr<Event> const eventPtr) = 0;
        virtual void handleGameLoop();

        virtual bool allowRenderDuringThePause();
    private:
        bool _paused = false;
        std::shared_ptr<Layer> _layer;
    protected:
        AbstractScreen();
        AbstractScreen(AbstractScreen const&) {};
        void operator=(AbstractScreen const&) {};
    };
}


#endif //PROJECT_HY454_ABSTRACTSCREEN_H
