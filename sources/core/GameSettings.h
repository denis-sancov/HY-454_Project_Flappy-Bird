//
// Created by Denis Sancov on 27/12/2016.
//

#ifndef PROJECT_HY454_GAMESETTINGS_H
#define PROJECT_HY454_GAMESETTINGS_H

#include <cstdint>

namespace csd {

    class GameSettings {
    public:
        static GameSettings& sharedInstance() {
            static GameSettings settings;
            return settings;
        }

        uint32_t moveLandAnimationDelay;
        uint32_t moveBackgroundAnimationDelay;


        /*
         *  Bird properties
         */

        uint32_t birdFrameRangeAnimationDelay;
        uint32_t birdGravityAnimationDelay;
        uint32_t birdRotationAnimationDelay;
        int      birdVelocityDelta;




        /*
         *      Scores for medals
         */

        uint32_t scoreForBronze;
        uint32_t scoreForSilver;
        uint32_t scoreForGold;
        uint32_t scoreForPlatinum;

        /*
         *      Pipe container sprite configuration properties
         */
        unsigned short numberOfPipesPairsPerGroup;
        unsigned short numberOfPipesPairsPerPyramideGroup;
        unsigned short numberOfPipesPairsPerStairsGroup;

        unsigned short scoreWhenToShowGroupPipePairs;
        unsigned short scoreWhenToShowPyramideGroupPipePairs;
        unsigned short scoreWhenToShowStairsGroupPipePairs;

        unsigned short heightBetweenPipes;
        unsigned short minPipeHeight;
        unsigned short distanceBetweenBarriers;


        /*
         *   Debug properties
         */

        bool drawCollisionBoxes;
        bool drawBoundingBoxes;

    private:
        GameSettings();
        GameSettings(GameSettings const&) {};
        void operator=(GameSettings const&) {};

        bool loadUserSettings();
        void restoreDefaults();
        void save();
    };
}


#endif //PROJECT_HY454_GAMESETTINGS_H
