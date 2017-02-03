//
// Created by Denis Sancov on 23/11/2016.
//

#include <iostream>
#include "MovingAnimator.h"

using namespace csd;

MovingAnimator::MovingAnimator(Layer *layer, MovingAnimation animation): _layer(layer), _animation(animation) {}

void MovingAnimator::progress(uint32_t ticksMS) {

    while (ticksMS > _lastTimeStampMS && ticksMS - _lastTimeStampMS >= _animation.getDelay()) {
        Point oldPosition = _layer->getPosition();
        Point newPosition = {
                oldPosition.x + _animation.getDeltaPoint().x,
                oldPosition.y + _animation.getDeltaPoint().y
        };
        _layer->setPosition(newPosition);
        if (progressCallback) {
            progressCallback();
        }

        if (!_animation.isContinuous()) {
            _status = AnimatorFinished;
            notifyStopped();
            break;
        } else {
            timeShift(_animation.getDelay());
            progress(ticksMS);
        }
    }
}