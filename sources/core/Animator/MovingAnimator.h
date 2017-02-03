//
// Created by Denis Sancov on 23/11/2016.
//

#ifndef PROJECT_HY454_MOVINGANIMATOR_H
#define PROJECT_HY454_MOVINGANIMATOR_H

#include "Animator.h"
#include "../Animation/MovingAnimation.h"

namespace csd {

    class MovingAnimator : public Animator {
    public:
        MovingAnimator(Layer *layer, MovingAnimation animation);

        void progress(uint32_t ticksMS) override;

        std::function<void(void)> progressCallback;
    private:
        Layer *_layer;
        MovingAnimation _animation;
    };
}


#endif //PROJECT_HY454_MOVINGANIMATOR_H
