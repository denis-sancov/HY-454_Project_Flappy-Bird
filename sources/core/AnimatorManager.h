//
// Created by Denis Sancov on 27/11/2016.
//

#ifndef PROJECT_HY454_ANIMATORMANAGER_H
#define PROJECT_HY454_ANIMATORMANAGER_H


#include <list>
#include "Animator/Animator.h"

namespace csd {

    class AnimatorManager {
    public:
        static AnimatorManager& shared() {
            static AnimatorManager manager;
            return manager;
        }

        void registerAnimator(std::shared_ptr<Animator> animator, bool run = false) {
            _suspended.push_back(animator);
            if (run) {
                markAsRunning(animator);
            }
        }

        void cancel(std::shared_ptr<Animator> animator) {
            _canceled.push_back(animator);
        }

        void markAsRunning(std::shared_ptr<Animator> animator) {
            _suspended.remove(animator);
            _running.push_back(animator);
            if (animator->hasFinished()) {
                animator->start(_ticks);
            }
        }
        void markAsSuspended(std::shared_ptr<Animator> animator) {
            animator->stop();
            _running.remove(animator);
            _suspended.push_back(animator);
        }

        void progress(uint32_t ticks) {
            _ticks = ticks;

            for (std::shared_ptr<Animator> animator : _canceled) {
                _running.remove(animator);
                _suspended.remove(animator);
            }
            _canceled.clear();

            for (std::shared_ptr<Animator> animator : _running) {
                animator->progress(ticks);
            }
        }
    private:
        uint32_t _ticks = 0;
        AnimatorManager() {};
        AnimatorManager(AnimatorManager const&);
        void operator=(AnimatorManager const&);

        std::list<std::shared_ptr<Animator> > _running, _suspended, _canceled;
    };
}


#endif //PROJECT_HY454_ANIMATORMANAGER_H
