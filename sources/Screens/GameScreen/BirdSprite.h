//
// Created by Denis Sancov on 20/11/2016.
//

#ifndef PROJECT_HY454_BIRDSPRITE_H
#define PROJECT_HY454_BIRDSPRITE_H


#include "../../core/Animator/FrameRangeAnimator.h"
#include "../../core/Animator/GravityAnimator.h"
#include "../../core/Animator/RotationAnimator.h"
#include "../../core/Sprites/ImageSprite.h"

namespace csd {

    typedef enum _birdState {
        BirdStateReady = 1,
        BirdStateCanFly,
        BirdStateFallingDown,
        BirdStateDead
    } BirtState;

    class BirdSprite : public ImageSprite {
    public:
        BirdSprite();
        ~BirdSprite();

        void        setState(BirtState state);
        BirtState   getState() const;

        void fly();

        void setVelocity(Point velocity) override;
        void setAngle(double angle) override;
    private:
        std::shared_ptr<FrameRangeAnimator> _frameRangeAnimator;
        std::shared_ptr<GravityAnimator>    _gravityAnimator;
        std::shared_ptr<RotationAnimator>   _rotationAnimator;

        BirtState _state;
    };
}


#endif //PROJECT_HY454_BIRDSPRITE_H
