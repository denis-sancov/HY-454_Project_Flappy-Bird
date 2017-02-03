//
// Created by Denis Sancov on 26/11/2016.
//

#ifndef PROJECT_HY454_ANIMATION_H
#define PROJECT_HY454_ANIMATION_H

#include <cstdint>

namespace csd {

    class Animation {
    public:
        Animation(uint32_t delay, bool continuous = true) {
            _delay = delay;
            _continuous = continuous;
        }

        void        setDelay(uint32_t delay)              { _delay = delay; }
        uint32_t    getDelay() const                      { return _delay; };

        void        setContinuous(bool continuous)        { _continuous = continuous; }
        bool        isContinuous() const                  { return _continuous; }
    private:
        uint32_t        _delay;
        bool            _continuous;
    };
}


#endif //PROJECT_HY454_ANIMATION_H
