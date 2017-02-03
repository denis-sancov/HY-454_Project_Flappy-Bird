//
// Created by Denis Sancov on 20/11/2016.
//

#ifndef PROJECT_HY454_TIMER_H
#define PROJECT_HY454_TIMER_H

#include <chrono>

namespace csd {
    class Timer {
    public:
        void start();
        void stop();

        void pause();
        void resume();

        bool isStarted() { return _started; }
        bool isPaused() { return _paused; }

        uint32_t getTicksInMS();
        uint32_t getTicksInSec();
    private:
        uint32_t _startTicks;
        uint32_t _pausedTicks;

        bool _paused = false;
        bool _started = false;

        uint32_t getTicksViaSteadyClock();
    };
}


#endif //PROJECT_HY454_TIMER_H
