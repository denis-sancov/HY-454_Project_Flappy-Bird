//
// Created by Denis Sancov on 29/12/2016.
//

#ifndef PROJECT_HY454_GROUPMOVINGANIMATOR_H
#define PROJECT_HY454_GROUPMOVINGANIMATOR_H



#include "Animator.h"
#include "../Animation/MovingAnimation.h"

namespace csd {

    class GroupMovingAnimator : public Animator {
    public:
        GroupMovingAnimator(MovingAnimation animation);

        void addLayer(std::shared_ptr<Layer> layer);
        void removeLayer(std::shared_ptr<Layer> layer);

        void progress(uint32_t ticksMS) override;
    private:
        std::vector<std::shared_ptr<Layer> > _layers;
        MovingAnimation _animation;
    };
}

#endif //PROJECT_HY454_GROUPMOVINGANIMATOR_H
