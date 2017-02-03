//
// Created by Denis Sancov on 01/01/2017.
//

#ifndef PROJECT_HY454_SOUNDSYSTEMINTERFACE_H
#define PROJECT_HY454_SOUNDSYSTEMINTERFACE_H

#include <string>

namespace csd {
    class SoundSystemInterface {
    public:
        virtual void playSound(std::string const filePath) = 0;
    protected:
        SoundSystemInterface() {};
        SoundSystemInterface(SoundSystemInterface const &) {};
        void operator=(SoundSystemInterface const &) {};
    };
}


#endif //PROJECT_HY454_SOUNDSYSTEMINTERFACE_H
