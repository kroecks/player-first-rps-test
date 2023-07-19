// RockPaperScissorsTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameController.h"

int main()
{
    std::cout << "Let the Game Begin!\n";

    GameController* gameControl = new GameController();

    gameControl->SetupGame();

    int maxRounds = 10000;
    int currentRound = 0;
    // Increment the rounds until 10,000
    while (++currentRound < maxRounds) {
        gameControl->UpdateRound();
    }

    std::cout << "Winning team: " << Constants::FighterTypeToDisplay((Constants::FighterType)gameControl->GetWinningTeam());

    // Clean it all up now
    gameControl->ShutDown();
    delete gameControl;
}