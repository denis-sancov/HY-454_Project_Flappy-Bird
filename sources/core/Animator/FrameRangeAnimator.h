//
// Created by Denis Sancov on 22/11/2016.
//

#ifndef PROJECT_HY454_FRAMERANGEANIMATOR_H
#define PROJECT_HY454_FRAMERANGEANIMATOR_H

#include "Animator.h"
#include "../Animation/FrameRangeAnimation.h"
#include "../Sprites/ImageSprite.h"

namespace csd {

    class FrameRangeAnimator : public Animator {
    private:
        ImageSprite *const _sprite;
        FrameRangeAnimation const _animation;
        unsigned short _currentFrame;
    public:
        FrameRangeAnimator(ImageSprite *const sprite, FrameRangeAnimation const animation);

        void progress(uint32_t ticksMS) override;
    };
}


#endif //PROJECT_HY454_FRAMERANGEANIMATOR_H
