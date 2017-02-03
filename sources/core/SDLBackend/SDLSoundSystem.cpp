//
// Created by Denis Sancov on 01/01/2017.
//

#include <iostream>
#include "SDLSoundSystem.h"

using namespace csd;

SDLSoundSystem::SDLSoundSystem() {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw std::invalid_argument("SDL_mixed could not be initialized!");
    }
}

SDLSoundSystem::~SDLSoundSystem() {
    for(auto it = _cachedSounds.begin(); it != _cachedSounds.end(); ++it) {
        Mix_FreeChunk(it->second);
        it->second = nullptr;
    }
    _cachedSounds.clear();
    Mix_Quit();
}

void SDLSoundSystem::playSound(std::string const filePath) {
    Mix_Chunk *chunk = nullptr;
    if (_cachedSounds.find(filePath) == _cachedSounds.end() ) {
        chunk = Mix_LoadWAV(filePath.c_str());
        if(chunk == nullptr) {
            throw std::invalid_argument("Failed to load sound effect from file " + filePath);
        }
        _cachedSounds.emplace(filePath, chunk);
    } else {
        chunk = _cachedSounds.at(filePath);
    }
    Mix_PlayChannel(-1, chunk, 0);
}



