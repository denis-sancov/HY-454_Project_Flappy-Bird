//
// Created by Denis Sancov on 26/11/2016.
//

#ifndef PROJECT_HY454_MOVINGANIMATION_H
#define PROJECT_HY454_MOVINGANIMATION_H

#include "Animation.h"
#include "../Geometry.h"

namespace csd {

    class MovingAnimation : public Animation {
    public:
        MovingAnimation(Point deltaPoint, uint32_t delay = 10, bool continuous = true): Animation(delay, continuous) {
            _deltaPoint  = deltaPoint;
        }

        void        setDeltaPoint(Point deltaPoint)      { _deltaPoint = deltaPoint; }
        Point       getDeltaPoint() const                { return _deltaPoint; }
    private:
        Point           _deltaPoint;
    };
}


#endif //PROJECT_HY454_MOVINGANIMATION_H
