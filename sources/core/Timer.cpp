//
// Created by Denis Sancov on 20/11/2016.
//

#include "Timer.h"
#include <iostream>

using namespace csd;
using namespace std::chrono;

uint32_t Timer::getTicksViaSteadyClock() {
    return static_cast<uint32_t>(duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count());
}

void Timer::start() {
    _started = true;
    _paused = false;

    _startTicks = this->getTicksViaSteadyClock();
    _pausedTicks = 0;
}

void Timer::stop() {
    _started = false;
    _paused = false;
    _startTicks = 0;
    _pausedTicks = 0;
}

void Timer::pause() {
    if (_started && !_paused) {
        _paused = true;
        _pausedTicks = this->getTicksViaSteadyClock() - _startTicks;
    }
}

void Timer::resume() {
    if (_started && _paused) {
        _paused = false;
        _startTicks = this->getTicksViaSteadyClock() - _pausedTicks;
        _pausedTicks = 0;
    }
}

uint32_t Timer::getTicksInMS() {
    uint32_t time = 0;
    if (_started) {
        time = (_paused) ? _pausedTicks : this->getTicksViaSteadyClock() - _startTicks;
    }
    return time;
}

uint32_t Timer::getTicksInSec() {
    return this->getTicksInMS() / 1000;
}
