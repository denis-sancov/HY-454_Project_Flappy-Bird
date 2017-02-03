//
// Created by Denis Sancov on 29/12/2016.
//

#ifndef PROJECT_HY454_ROTATIONANIMATOR_H
#define PROJECT_HY454_ROTATIONANIMATOR_H


#include "Animator.h"
#include "../Animation/RotationAnimation.h"

namespace csd {

    class RotationAnimator : public Animator {
    public:
        RotationAnimator(Layer *layer, RotationAnimation const animation);

        void progress(uint32_t ticksMS) override;
    private:
        Layer *_layer;
        RotationAnimation  _animation;
    };
}


#endif //PROJECT_HY454_ROTATIONANIMATOR_H
