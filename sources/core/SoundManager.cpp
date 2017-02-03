//
// Created by Denis Sancov on 01/01/2017.
//

#include "SoundManager.h"
#include "../GameDelegate.h"

using namespace csd;

SoundManager::SoundManager() {
    _sounds = {
            {SoundHit, "sfx_hit.ogg"},
            {SoundPoint, "sfx_point.ogg"},
            {SoundWooshing, "sfx_wooshing.ogg"},
            {SoundDie, "sfx_die.ogg"},
            {SoundWing, "sfx_wing.ogg"}
    };
};

void SoundManager::playSound(SoundType soundType) {
    std::string filePath =  "Resources/Sounds/" + _sounds.at(soundType);
    csd::GameDelegate& game = csd::GameDelegate::sharedInstance();
    game.getGameEngine()->soundSystem()->playSound(filePath);
}