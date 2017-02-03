//
// Created by Denis Sancov on 03/01/2017.
//

#ifndef PROJECT_HY454_USERGAMEDATA_H
#define PROJECT_HY454_USERGAMEDATA_H


#include <vector>

namespace csd {
    class UserGameData {
    public:
        static UserGameData& sharedInstance() {
            static UserGameData userGameData;
            return userGameData;
        }

        void setBestScore(unsigned int score);
        unsigned int getPreviousBestScore() const;

    private:
        UserGameData();
        UserGameData(UserGameData const&) {};
        void operator=(UserGameData const&) {};

        unsigned int _bestScore = 0;
    };
}


#endif //PROJECT_HY454_USERGAMEDATA_H
