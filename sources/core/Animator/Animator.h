//
// Created by Denis Sancov on 22/11/2016.
//

#ifndef PROJECT_HY454_ANIMATOR_H
#define PROJECT_HY454_ANIMATOR_H

#include <functional>
#include "../Sprites/Layer.h"

namespace csd {

    typedef enum _animatorStatus {
        AnimatorFinished = 0,
        AnimatorRunning,
        AnimatorStopped
    } AnimatorStatus;

    class Animator {
    public:
        Animator();

        virtual ~Animator() {};

        void start(uint32_t ticksMS = 0);
        void stop();

        void timeShift(uint32_t offset);

        virtual void progress(uint32_t ticksMS) = 0;

        bool hasFinished() const { return _status != AnimatorRunning; }
    private:
        std::function<void()> _onFinish = nullptr;
    protected:
        uint32_t _lastTimeStampMS;
        AnimatorStatus _status;

        void notifyStopped();
    };
}


#endif //PROJECT_HY454_ANIMATOR_H
