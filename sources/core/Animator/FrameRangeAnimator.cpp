//
// Created by Denis Sancov on 22/11/2016.
//

#include <iostream>
#include "FrameRangeAnimator.h"

using namespace csd;

FrameRangeAnimator::FrameRangeAnimator(ImageSprite *const sprite, FrameRangeAnimation const animation):
        _sprite(sprite), _animation(animation), _currentFrame(0) {}

void FrameRangeAnimator::progress(uint32_t ticksMS) {
    while (ticksMS > _lastTimeStampMS && ticksMS - _lastTimeStampMS >= _animation.getDelay()) {
        if (_currentFrame == _animation.getEndFrame()) {
            _currentFrame = _animation.getStartFrame();
        } else {
            _currentFrame += 1;
        }

        _sprite->setFrameToDisplay(_currentFrame);
        timeShift(_animation.getDelay());

        if (_currentFrame == _animation.getEndFrame() && !_animation.isContinuous()) {
            _status = AnimatorFinished;
            notifyStopped();
            return;
        }
    }
}