//
// Created by Denis Sancov on 26/11/2016.
//

#ifndef PROJECT_HY454_FRAMERANGEANIMATION_H
#define PROJECT_HY454_FRAMERANGEANIMATION_H

#include "Animation.h"

namespace csd {

    class FrameRangeAnimation : public Animation {
    public:
        FrameRangeAnimation(unsigned short start, unsigned short end, uint32_t delay = 10, bool continuous = true)
                : Animation(delay, continuous) {
            _start = start;
            _end = end;
        }

        unsigned short getStartFrame() const { return _start; }
        unsigned short getEndFrame()   const { return _end; }

    private:
        unsigned short  _start, _end;

    };
}


#endif //PROJECT_HY454_FRAMERANGEANIMATION_H
