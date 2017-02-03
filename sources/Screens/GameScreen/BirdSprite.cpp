//
// Created by Denis Sancov on 20/11/2016.
//

#include <iostream>
#include "BirdSprite.h"
#include "../../core/AnimatorManager.h"
#include "../../core/GameSettings.h"
#include <cmath>

using namespace csd;

BirdSprite::BirdSprite():ImageSprite("Resources/Bitmaps/FlappyBird.bmp", (Size){68, 48}) {
    _state = BirdStateReady;
    this->setFrameToDisplay(0);

    GameSettings &settings = GameSettings::sharedInstance();

    unsigned short finalFrame = this->framesCount();

    FrameRangeAnimation frameRangeAnimation = FrameRangeAnimation(0, finalFrame, settings.birdFrameRangeAnimationDelay);
    _frameRangeAnimator = std::shared_ptr<FrameRangeAnimator>(new FrameRangeAnimator(this, frameRangeAnimation));
    AnimatorManager::shared().registerAnimator(_frameRangeAnimator, false);

    GravityAnimation gravityAnimation = GravityAnimation(1, settings.birdGravityAnimationDelay, true);
    _gravityAnimator = std::shared_ptr<GravityAnimator>(new GravityAnimator(this, gravityAnimation));
    AnimatorManager::shared().registerAnimator(_gravityAnimator, false);

    RotationAnimation rotationAnimation = RotationAnimation(1.f, settings.birdRotationAnimationDelay, true);
    _rotationAnimator = std::shared_ptr<RotationAnimator>(new RotationAnimator(this, rotationAnimation));
    AnimatorManager::shared().registerAnimator(_rotationAnimator, false);
}

void BirdSprite::setState(BirtState state) {
    if (state == _state) {
        return;
    }
    switch (state) {
        case BirdStateCanFly: {
            AnimatorManager::shared().markAsRunning(_frameRangeAnimator);
            AnimatorManager::shared().markAsRunning(_gravityAnimator);
            AnimatorManager::shared().markAsRunning(_rotationAnimator);
            break;
        }
        case BirdStateFallingDown: {
            AnimatorManager::shared().markAsSuspended(_frameRangeAnimator);
            break;
        }
        default: {
            AnimatorManager::shared().markAsSuspended(_frameRangeAnimator);
            AnimatorManager::shared().markAsSuspended(_gravityAnimator);
            AnimatorManager::shared().markAsSuspended(_rotationAnimator);
        }
    }
    _state = state;
}

BirtState BirdSprite::getState() const {
    return _state;
}

void BirdSprite::fly() {
    this->setState(BirdStateCanFly);
    Point velocity = this->getVelocity();

    GameSettings &settings = GameSettings::sharedInstance();
    velocity.y = -settings.birdVelocityDelta;

    this->setVelocity(velocity);
}

void BirdSprite::setVelocity(Point velocity) {
    Layer::setVelocity(velocity);
    double rotationDegree = this->getAngle();
    if (velocity.y < 0) {
        AnimatorManager::shared().markAsRunning(_frameRangeAnimator);
        AnimatorManager::shared().markAsRunning(_rotationAnimator);
        rotationDegree = -25.f;
    }
    this->setAngle(rotationDegree);
}

void BirdSprite::setAngle(double angle) {
    if (angle > 0) {
        AnimatorManager::shared().markAsSuspended(_frameRangeAnimator);
        this->setFrameToDisplay(1);
    }
    if (angle > 90.f) {
        angle = 90.f;
    }
    Layer::setAngle(angle);
}


BirdSprite::~BirdSprite() {
    AnimatorManager::shared().cancel(_frameRangeAnimator);
    AnimatorManager::shared().cancel(_gravityAnimator);
    AnimatorManager::shared().cancel(_rotationAnimator);
}