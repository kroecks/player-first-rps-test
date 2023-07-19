#pragma once

#include <string>

class Constants {
public:
    enum FighterType {
        Invalid = -1,
        Rock = 0,
        Paper = 1,
        Scissors = 2,
        TeamCount = 2,
    };

    inline static std::string FighterTypeToDisplay(FighterType fighter) {
        switch (fighter) {
        case Rock:
            return "Rock";
        case Scissors:
            return "Scissors";
        case Paper:
            return "Paper";
        default:
            return "INVALID";
        }
    }
};