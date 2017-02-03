//
// Created by Denis Sancov on 16/01/2017.
//

#ifndef PROJECT_HY454_BARRIERINTERFACE_H
#define PROJECT_HY454_BARRIERINTERFACE_H

#include "../../../core/Sprites/Layer.h"

namespace csd {
    class BarrierInterface : public Layer {
    public:

        void setPassed(bool const passed) { _passed = passed; }
        bool isPassed() const             { return _passed; }

        void setPaused(bool const paused) { _paused = paused; }
        bool isPaused() const             { return _paused; }

        virtual unsigned int getScoreForPassing() const = 0;
    private:
        bool _passed = false;
        bool _paused = false;
    protected:
        BarrierInterface():Layer() {};
        BarrierInterface(BarrierInterface const&) {};
        void operator=(BarrierInterface const&) {};
    };
}

#endif //PROJECT_HY454_BARRIERINTERFACE_H
