//
// Created by Denis Sancov on 27/12/2016.
//

#include <iostream>
#include <fstream>
#include "GameSettings.h"
#include "../../third-part/json/json.hpp"

using namespace csd;
using json = nlohmann::json;

GameSettings::GameSettings() {
    this->restoreDefaults();
    if (!loadUserSettings()) {
        save();
    }
}

bool GameSettings::loadUserSettings() {
    std::ifstream configFile("config.json");
    if (!configFile.good()) {
        return false;
    }

    json userJsonConfig;
    configFile >> userJsonConfig;
    if (userJsonConfig == nullptr) {
        return false;
    }


    json gameScreenConfig = userJsonConfig["game_screen"];
    if (gameScreenConfig != nullptr) {
        moveLandAnimationDelay       = static_cast<uint32_t>(gameScreenConfig.value("moveLandAnimationDelay", 5));
        moveBackgroundAnimationDelay = static_cast<uint32_t>(gameScreenConfig.value("moveBackgroundAnimationDelay", 30));
    }

    json bird = userJsonConfig["bird"];
    if (bird != nullptr) {
        birdFrameRangeAnimationDelay    = static_cast<uint32_t>(bird.value("birdFrameRangeAnimationDelay", 50));
        birdGravityAnimationDelay       = static_cast<uint32_t>(bird.value("birdGravityAnimationDelay", 25));
        birdRotationAnimationDelay      = static_cast<uint32_t>(bird.value("birdRotationAnimationDelay", 8));
        birdVelocityDelta               = bird.value("birdVelocityDelta", 12);
    }

    json reward = userJsonConfig["reward"];
    if (reward != nullptr) {
        scoreForBronze   = static_cast<uint32_t>(reward.value("scoreForBronze", 5));
        scoreForSilver   = static_cast<uint32_t>(reward.value("scoreForSilver", 10));
        scoreForGold     = static_cast<uint32_t>(reward.value("scoreForGold", 20));
        scoreForPlatinum = static_cast<uint32_t>(reward.value("scoreForPlatinum", 50));
    }

    json pipes = userJsonConfig["pipes"];

    if (pipes != nullptr) {
        numberOfPipesPairsPerGroup          = static_cast<unsigned short>(pipes.value("numberOfPipesPairsPerGroup", 5));
        numberOfPipesPairsPerPyramideGroup  = static_cast<unsigned short>(pipes.value("numberOfPipesPairsPerPyramideGroup", 8));
        numberOfPipesPairsPerStairsGroup    = static_cast<unsigned short>(pipes.value("numberOfPipesPairsPerStairsGroup", 6));

        scoreWhenToShowGroupPipePairs           = static_cast<unsigned short>(pipes.value("scoreWhenToShowGroupPipePairs", 5));
        scoreWhenToShowPyramideGroupPipePairs   = static_cast<unsigned short>(pipes.value("scoreWhenToShowPyramideGroupPipePairs", 15));
        scoreWhenToShowStairsGroupPipePairs     = static_cast<unsigned short>(pipes.value("scoreWhenToShowStairsGroupPipePairs", 10));

        heightBetweenPipes                  = static_cast<unsigned short>(pipes.value("heightBetweenPipes", 240));
        minPipeHeight                       = static_cast<unsigned short>(pipes.value("minPipeHeight", 80));
        distanceBetweenBarriers       = static_cast<unsigned short>(pipes.value("distanceBetweenBarriers", 200));
    }

    json debug = userJsonConfig["debug"];
    if (debug != nullptr) {
        drawCollisionBoxes = debug.value("drawCollisionBoxes", false);
        drawBoundingBoxes = debug.value("drawBoundingBoxes", false);
    }

    this->save();
    return true;
}

void GameSettings::restoreDefaults() {
    moveLandAnimationDelay = 4;
    moveBackgroundAnimationDelay = 30;

    birdFrameRangeAnimationDelay = 50;
    birdGravityAnimationDelay = 25;
    birdRotationAnimationDelay = 8;
    birdVelocityDelta = 12;

    scoreForBronze = 5;
    scoreForSilver = 10;
    scoreForGold = 20;
    scoreForPlatinum = 50;


    numberOfPipesPairsPerGroup = 5;
    numberOfPipesPairsPerPyramideGroup = 8;
    numberOfPipesPairsPerStairsGroup = 6;

    scoreWhenToShowGroupPipePairs = 1;
    scoreWhenToShowPyramideGroupPipePairs = 2;
    scoreWhenToShowStairsGroupPipePairs = 3;

    heightBetweenPipes = 240;
    minPipeHeight = 80;
    distanceBetweenBarriers = 200;

    drawCollisionBoxes = false;
    drawBoundingBoxes = false;
}

void GameSettings::save() {
    json jsonObject = {
            {"debug", {
                              {"drawCollisionBoxes", drawCollisionBoxes},
                              {"drawBoundingBoxes", drawBoundingBoxes},

                      }},
            {"game_screen", {
                                    {"moveLandAnimationDelay", moveLandAnimationDelay},
                                    {"moveBackgroundAnimationDelay", moveBackgroundAnimationDelay}
                            }},
            {"bird", {
                             {"birdFrameRangeAnimationDelay", birdFrameRangeAnimationDelay},
                             {"birdGravityAnimationDelay", birdGravityAnimationDelay},
                             {"birdRotationAnimationDelay", birdRotationAnimationDelay},
                             {"birdVelocityDelta", birdVelocityDelta}
                     }},
            {"pipes", {
                              {"numberOfPipesPairsPerGroup", numberOfPipesPairsPerGroup},
                              {"numberOfPipesPairsPerPyramideGroup", numberOfPipesPairsPerPyramideGroup},
                              {"numberOfPipesPairsPerStairsGroup", numberOfPipesPairsPerStairsGroup},
                              {"heightBetweenPipes", heightBetweenPipes},
                              {"minPipeHeight", minPipeHeight},
                              {"distanceBetweenBarriers", distanceBetweenBarriers},
                              {"scoreWhenToShowGroupPipePairs", scoreWhenToShowGroupPipePairs},
                              {"scoreWhenToShowPyramideGroupPipePairs", scoreWhenToShowPyramideGroupPipePairs},
                              {"scoreWhenToShowStairsGroupPipePairs", scoreWhenToShowStairsGroupPipePairs},
                      }},
            {"reward", {
                               {"scoreForBronze", scoreForBronze},
                               {"scoreForSilver", scoreForSilver},
                               {"scoreForGold", scoreForGold},
                               {"scoreForPlatinum", scoreForPlatinum}
                       }}
    };

    std::ofstream out("config.json");
    out << jsonObject.dump(4);
    out.close();
}