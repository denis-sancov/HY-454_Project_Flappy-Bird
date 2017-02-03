//
// Created by Denis Sancov on 29/12/2016.
//

#include "GroupMovingAnimator.h"
#include <algorithm>

using namespace csd;

GroupMovingAnimator::GroupMovingAnimator( MovingAnimation animation):_animation(animation) {}

void GroupMovingAnimator::addLayer(std::shared_ptr<Layer> layer) {
    _layers.push_back(layer);
}

void GroupMovingAnimator::removeLayer(std::shared_ptr<Layer> layer) {
    _layers.erase(std::remove(_layers.begin(), _layers.end(), layer), _layers.end());
}

void GroupMovingAnimator::progress(uint32_t ticksMS) {
    while (ticksMS > _lastTimeStampMS && ticksMS - _lastTimeStampMS >= _animation.getDelay()) {

        Point oldPosition;
        for (auto layer : _layers) {

            oldPosition = layer->getPosition();
            layer->setPosition(Point{
                    oldPosition.x + _animation.getDeltaPoint().x,
                    oldPosition.y + _animation.getDeltaPoint().y
            });
        }

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