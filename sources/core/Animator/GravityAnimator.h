//
// Created by Denis Sancov on 21/12/2016.
//

#ifndef PROJECT_HY454_GRAVITYANIMATOR_H
#define PROJECT_HY454_GRAVITYANIMATOR_H

#include "Animator.h"
#include "../Animation/GravityAnimation.h"

namespace csd {

    class GravityAnimator : public Animator {
    public:
        GravityAnimator(Layer *layer, GravityAnimation const animation);

        void progress(uint32_t ticksMS) override;
    private:
        Layer *_layer;
        GravityAnimation  _animation;
    };
}


#endif //PROJECT_HY454_GRAVITYANIMATOR_H
