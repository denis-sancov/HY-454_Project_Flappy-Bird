//
// Created by Denis Sancov on 03/01/2017.
//

#include "UserGameData.h"
#include <iostream>
#include <fstream>

using namespace csd;
using namespace std;

UserGameData::UserGameData() {
    std::ifstream file("UserScore.data");

    if (!file.eof() && !file.fail()) {
        file.read(reinterpret_cast<char *>(&_bestScore), sizeof(_bestScore));
    }
}

void UserGameData::setBestScore(unsigned int score) {
    _bestScore = score;

    ofstream out("UserScore.data", ios::out | ios::binary);
    out.write(reinterpret_cast<const char *>(&_bestScore), sizeof(_bestScore));
    out.close();
}

unsigned int UserGameData::getPreviousBestScore() const {
    return _bestScore;
}