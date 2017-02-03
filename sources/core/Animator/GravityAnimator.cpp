//
// Created by Denis Sancov on 21/12/2016.
//

#include <iostream>
#include <cmath>
#include "GravityAnimator.h"

using namespace csd;

GravityAnimator::GravityAnimator(Layer *layer, GravityAnimation const animation): _layer(layer), _animation(animation) {

}

void GravityAnimator::progress(uint32_t ticksMS) {

    while (ticksMS > _lastTimeStampMS && ticksMS - _lastTimeStampMS >= _animation.getDelay()) {
        Point velocity = _layer->getVelocity();
        velocity.y +=_animation.getGravity();
        _layer->setVelocity(velocity);

        if (!_animation.isContinuous()) {
            _status = AnimatorFinished;
            notifyStopped();
            break;
        } else {
            timeShift(_animation.getDelay());
            this->progress(ticksMS);
        }
    }
}
