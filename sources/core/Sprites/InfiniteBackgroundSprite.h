//
// Created by Denis Sancov on 17/01/2017.
//

#ifndef PROJECT_HY454_INFINITEBACKGROUNDSPRITE_H
#define PROJECT_HY454_INFINITEBACKGROUNDSPRITE_H

#include "../Animator/MovingAnimator.h"

namespace csd {

    class InfiniteBackgroundSprite : public Layer {
    public:
        InfiniteBackgroundSprite(std::string const& fileNamed, Point const& delta, uint32_t delay);
        ~InfiniteBackgroundSprite();

        void setPaused(bool const pause);
        bool isPaused() const;

        Rect getBoundingBox() const override;

    private:
        std::shared_ptr<BitmapInterface> _bitmap;
        std::shared_ptr<MovingAnimator>  _animator;
        bool _paused = false;

        void readyToRender() override;
    };
}


#endif //PROJECT_HY454_INFINITEBACKGROUNDSPRITE_H
