//
// Created by Denis Sancov on 01/01/2017.
//

#ifndef PROJECT_HY454_SDLSOUNDSYSTEM_H
#define PROJECT_HY454_SDLSOUNDSYSTEM_H

#include <SDL_mixer.h>
#include <map>
#include "../GameEngineAbstract/SoundSystemInterface.h"

namespace csd {
    class SDLSoundSystem : public SoundSystemInterface{
    public:
        SDLSoundSystem();
        ~SDLSoundSystem();

        void playSound(std::string const filePath) override;
    private:
        std::map<std::string , Mix_Chunk *> _cachedSounds;
    };
}


#endif //PROJECT_HY454_SDLSOUNDSYSTEM_H
