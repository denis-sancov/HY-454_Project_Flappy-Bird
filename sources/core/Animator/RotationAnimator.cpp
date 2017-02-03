//
// Created by Denis Sancov on 29/12/2016.
//

#include "RotationAnimator.h"


using namespace csd;

RotationAnimator::RotationAnimator(Layer *layer, RotationAnimation const animation):_layer(layer), _animation(animation) {

}

void RotationAnimator::progress(uint32_t ticksMS) {
    while (ticksMS > _lastTimeStampMS && ticksMS - _lastTimeStampMS >= _animation.getDelay()) {
        double angle = _layer->getAngle();
        angle += _animation.getRotationDelta();
        _layer->setAngle(angle);

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