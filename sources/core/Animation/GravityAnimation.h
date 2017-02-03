//
// Created by Denis Sancov on 21/12/2016.
//

#ifndef PROJECT_HY454_GRAVITYANIMATION_H
#define PROJECT_HY454_GRAVITYANIMATION_H


#include "Animation.h"

namespace csd {

    class GravityAnimation : public Animation {
    public:
        GravityAnimation(float gravity, uint32_t delay, bool continuous) : Animation(delay, continuous) {
            _gravity = gravity;
        }

        void         setGravity(float gravity)  { _gravity = gravity; }
        float        getGravity() const         { return _gravity; }
    private:
        float           _gravity = 0.5f;
    };
}

#endif //PROJECT_HY454_GRABITYANIMATION_H
