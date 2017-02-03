//
// Created by Denis Sancov on 17/01/2017.
//

#include "InfiniteBackgroundSprite.h"
#include "../AnimatorManager.h"

using namespace csd;

InfiniteBackgroundSprite::InfiniteBackgroundSprite(std::string const& fileNamed, Point const& delta, uint32_t delay) {
    _bitmap = getRenderer()->bitmapFromFile(fileNamed);
    setSize(_bitmap->getOriginalSize());

    MovingAnimation moveLandAnimation = MovingAnimation(delta, delay);
    _animator = std::shared_ptr<MovingAnimator>(new MovingAnimator(this, moveLandAnimation));

    _animator->progressCallback = [this] {
        Point point = this->getPosition();
        if (point.x <= -this->getSize().width) {
            point.x = 0;
            this->setPosition(point);
        }
    };
    AnimatorManager::shared().registerAnimator(_animator, true);
}

Rect InfiniteBackgroundSprite::getBoundingBox() const {
    Rect rect = Layer::getBoundingBox();
    rect.origin.x = 0;
    return rect;
}

void InfiniteBackgroundSprite::setPaused(bool const pause) {
    if (pause) {
        AnimatorManager::shared().markAsSuspended(_animator);
    } else {
        AnimatorManager::shared().markAsRunning(_animator);
    }
    _paused = pause;
}

bool InfiniteBackgroundSprite::isPaused() const {
    return _paused;
}

void InfiniteBackgroundSprite::readyToRender() {
    Layer::readyToRender();

    int xOffset = getPosition().x;
    while (xOffset < getSize().width) {
        _bitmap->setPosition(Point{
                xOffset, getPosition().y
        });
        _bitmap->setScaledSize(Size{
                _bitmap->getOriginalSize().width,
                getSize().height
        });
        _bitmap->renderCopy();
        xOffset += _bitmap->getOriginalSize().width;
    }
}

InfiniteBackgroundSprite::~InfiniteBackgroundSprite() {
    AnimatorManager::shared().cancel(_animator);
}