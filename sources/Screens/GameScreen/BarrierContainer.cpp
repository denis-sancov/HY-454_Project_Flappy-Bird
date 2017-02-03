//
// Created by Denis Sancov on 15/01/2017.
//

#include "BarrierContainer.h"
#include "../../core/GameSettings.h"
#include "Barriers/BarrierInterface.h"
#include "../../core/AnimatorManager.h"
#include "Barriers/PipeBarrierSprite.h"

using namespace csd;

BarrierContainer::BarrierContainer(std::function<void(unsigned int)> onBarrierPass) {
    _onBarrierPass = onBarrierPass;

    Point delta = Point {-1, 0};
    GameSettings& settings = GameSettings::sharedInstance();

    MovingAnimation moveBarriersAnimation = MovingAnimation(delta, settings.moveLandAnimationDelay);
    _animator = std::shared_ptr<GroupMovingAnimator>(new GroupMovingAnimator(moveBarriersAnimation));

    AnimatorManager::shared().registerAnimator(_animator, false);
}

bool BarrierContainer::isPaused() const {
    return _paused;
}

void BarrierContainer::setPaused(bool const paused) {
    _paused = paused;
    if (paused) {
        AnimatorManager::shared().markAsSuspended(_animator);
    } else {
        AnimatorManager::shared().markAsRunning(_animator);
    }

    for (auto sublayer : getSublayers()) {
        std::dynamic_pointer_cast<BarrierInterface>(sublayer)->setPaused(paused);
    }
}

void BarrierContainer::reset() {
    _score = 0;

    for (auto sublayer : getSublayers()) {
        _animator->removeLayer(sublayer);
        this->removeSublayer(sublayer);
    }
}

bool BarrierContainer::intersectsLayer(std::shared_ptr<Layer> layer) {
    bool intersects = false;

    for (auto sublayer : getSublayers()) {
        auto barrier = std::dynamic_pointer_cast<BarrierInterface>(sublayer);
        if (!barrier->isPassed()) {
            if (barrier->getBoundingBox().right() < layer->getPosition().x) {
                barrier->setPassed(true);
                _score += barrier->getScoreForPassing();
                _onBarrierPass(barrier->getScoreForPassing());
                break;
            }
        }

        if (layer->getBoundingBox().right() >= barrier->getPosition().x &&
                layer->getPosition().x <= barrier->getBoundingBox().right()) {
            intersects = ((layer->getPosition().y < 0) || (barrier->collisionBoxIntersection(layer)));
            if (intersects) {
                break;
            }

        }
    }


    return intersects;
}


void BarrierContainer::readyToRender() {
    Layer::readyToRender();



    GameSettings& settings = GameSettings::sharedInstance();
    int distanceBetweenContainers = settings.distanceBetweenBarriers;

    int lastOffset = 0;

    auto sublayers = getSublayers();

    if (sublayers.size() > 0) {
        auto frontBarrier = std::dynamic_pointer_cast<BarrierInterface>(sublayers.front());
        if (frontBarrier->getBoundingBox().right() < -20) {
            _animator->removeLayer(frontBarrier);
            removeSublayer(0);
        }
        auto lastBarrier = std::dynamic_pointer_cast<BarrierInterface>(sublayers.back());
        lastOffset = lastBarrier->getBoundingBox().right() + distanceBetweenContainers;
    } else {
        lastOffset = getSize().width + 20;
    }


    unsigned short approximativeMaxAmountOfContainers = static_cast<unsigned short>(getSize().width / distanceBetweenContainers);

    for (unsigned short i = 0; i < (approximativeMaxAmountOfContainers - sublayers.size()); ++i) {
        auto maxDifficultyPipeType = PipeBarrierSprite::PipeTypeClassic;
        if (_score >= settings.scoreWhenToShowPyramideGroupPipePairs) {
            maxDifficultyPipeType = PipeBarrierSprite::PipeTypeGroupPyramide;
        }
        else if (_score >= settings.scoreWhenToShowStairsGroupPipePairs) {
            maxDifficultyPipeType = PipeBarrierSprite::PipeTypeGroupStairs;
        }
        else if (_score >= settings.scoreWhenToShowGroupPipePairs) {
            maxDifficultyPipeType = PipeBarrierSprite::PipeTypeGroup;
        }

        auto time = _clock.now().time_since_epoch().count();
        _generatorEngine.seed(static_cast<unsigned int>(time));

        _pipeTypesDistribution = std::uniform_int_distribution<unsigned int>(
                PipeBarrierSprite::PipeTypeClassic, static_cast<unsigned int>(maxDifficultyPipeType)
        );


        PipeBarrierSprite::PipeType type = static_cast<PipeBarrierSprite::PipeType>(_pipeTypesDistribution(_generatorEngine));

        auto pipeBarrierSprite = std::shared_ptr<PipeBarrierSprite>(new PipeBarrierSprite(type));
        pipeBarrierSprite->setHidden(true);
        pipeBarrierSprite->setZIndex(1);
        pipeBarrierSprite->setPosition(Point {
                lastOffset, 0
        });
        addSublayer(pipeBarrierSprite);

        _animator->addLayer(pipeBarrierSprite);

        lastOffset = pipeBarrierSprite->getBoundingBox().right() + distanceBetweenContainers;
    }


    for (auto barrier : sublayers) {
        barrier->setHidden(barrier->getPosition().x > (getSize().width + 20));
    }
}

BarrierContainer::~BarrierContainer() {
    AnimatorManager::shared().cancel(_animator);
}