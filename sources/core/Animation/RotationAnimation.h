//
// Created by Denis Sancov on 29/12/2016.
//

#ifndef PROJECT_HY454_ROTATIONANIMATION_H
#define PROJECT_HY454_ROTATIONANIMATION_H

#include "Animation.h"

namespace csd {

    class RotationAnimation : public Animation {
    public:
        RotationAnimation(double rotationDelta, uint32_t delay, bool continuous) : Animation(delay, continuous) {
            _rotationDelta = rotationDelta;
        }

        void          setRotationDelta(double rotationDelta)  { _rotationDelta = rotationDelta; }
        double        getRotationDelta() const                { return _rotationDelta; }
    private:
        double _rotationDelta = 0.f;
    };
}

#endif //PROJECT_HY454_ROTATIONANIMATION_H
