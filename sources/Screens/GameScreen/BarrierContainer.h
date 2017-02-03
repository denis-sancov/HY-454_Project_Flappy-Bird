//
// Created by Denis Sancov on 15/01/2017.
//

#ifndef PROJECT_HY454_BARRIERCONTAINER_H
#define PROJECT_HY454_BARRIERCONTAINER_H

#include <chrono>
#include <random>
#include "../../core/Animator/GroupMovingAnimator.h"

namespace csd {


    class BarrierContainer : public Layer {

    public:
        BarrierContainer(std::function<void(unsigned int)> onBarrierPass);
        ~BarrierContainer();

        bool isPaused() const;
        void setPaused(bool const paused);

        void reset();
        bool intersectsLayer(std::shared_ptr<Layer> layer);

    private:
        bool _paused = true;

        unsigned int _score = 0;

        std::shared_ptr<GroupMovingAnimator> _animator;
        std::mt19937 _generatorEngine;
        std::uniform_int_distribution<unsigned int> _pipeTypesDistribution;
        std::chrono::high_resolution_clock _clock;

        std::function<void(unsigned int score)> _onBarrierPass;

    protected:
        void readyToRender() override;
    };
}


#endif //PROJECT_HY454_BARRIERCONTAINER_H
