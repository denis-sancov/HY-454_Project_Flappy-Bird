//
// Created by Denis Sancov on 01/01/2017.
//

#ifndef PROJECT_HY454_SOUNDMANAGER_H
#define PROJECT_HY454_SOUNDMANAGER_H

#include <map>

namespace csd {
    class SoundManager {
    public:
        typedef enum _sound {
            SoundHit = 1,
            SoundPoint,
            SoundWooshing,
            SoundDie,
            SoundWing
        } SoundType;

        static SoundManager& sharedInstance() {
            static SoundManager manager;
            return manager;
        }
        void playSound(SoundType soundType);

    private:
        SoundManager();
        SoundManager(SoundManager const &) {};
        void operator=(SoundManager const &) {};
        std::map<SoundType, std::string> _sounds;
    };
}


#endif //PROJECT_HY454_SOUNDMANAGER_H
