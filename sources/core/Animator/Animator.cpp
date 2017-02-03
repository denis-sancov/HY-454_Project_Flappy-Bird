//
// Created by Denis Sancov on 23/11/2016.
//

#include <iostream>
#include "Animator.h"

using namespace csd;

Animator::Animator() {
    _status = AnimatorFinished;
}

void Animator::notifyStopped() {
    if (_onFinish != nullptr) {
        _onFinish();
    }
}

void Animator::timeShift(uint32_t offset) {
    _lastTimeStampMS += offset;
}

void Animator::start(uint32_t ticksMS) {
    _lastTimeStampMS = ticksMS;
    _status = AnimatorRunning;
}

void Animator::stop() {
    if (!hasFinished()) {
        _status = AnimatorStopped;
        notifyStopped();
    }
}