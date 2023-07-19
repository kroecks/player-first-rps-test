#include "GameController.h"

#include "Fighter.h"
#include "GameTeam.h"

#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstring>


// Utility method to convert char into enum
Constants::FighterType GetFighterType(char sVal) {
        // Fighter type is just a single character, so get char-at 0
    // Also, make sure it's lowercase just in case
    switch (tolower(sVal)) {
        case 'r': {
            return Constants::FighterType::Rock;
        }
        case 'p': {
            return Constants::FighterType::Paper;
        }
        case 's': {
            return Constants::FighterType::Scissors;
        }
        default:
            // Return rock for error case
            return Constants::FighterType::Invalid;
    }
}

void GameController::ShutDown() {
    for (auto kvp : gameTeams) {
        delete kvp.second;
    }

    gameTeams.clear();

    for (auto fighter : allFighters) {
        delete fighter;
    }

    allFighters.clear();
}

void GameController::SetupGame() {
    std::string line;
    std::ifstream input;
    input.open("input.txt");

    if (input.is_open())
    {
        while (getline(input, line))
        {
            std::stringstream ss(line);
            int i = 0;
            char fighterType;
            int x = 0, y = 0;
            while (ss.good())
            {
                std::string substr;
                getline(ss, substr, ',');
                if (i == 0)
                {
                    // pull out the type here
                    // type = substr[0];
                    fighterType = substr[0];
                }
                else if (i == 1)
                {
                    x = stoll(substr);   
                }
                else if (i == 2) { // pull out the y loc
                    y = stoll(substr);
                }
                ++i;
            }

            // We've pulled out the type, x, and y
            // create a fighter and add it to the game
            auto fighterTeam = GetFighterType(fighterType);
            Fighter* newFighter = new Fighter(this, fighterTeam, x, y);
            allFighters.push_back(newFighter);
            AddPlayerToGame(newFighter);
        }
        input.close();
    }
    else {
        std::cout << "File not found!";
    }
}

void GameController::AddPlayerToGame(Fighter* fighter) {
    std::cout << "Adding fighter to game: " << fighter->GetDisplayString() << "\n";

    if (gameTeams.count(fighter->GetFighterType()) == 0) {
        // If the team doesn't exist yet, make it
        gameTeams.insert({ fighter->GetFighterType(), new GameTeam(this) });
    }

    TakePosition(fighter->GetX(), fighter->GetY(), fighter);

    auto found = gameTeams.find(fighter->GetFighterType());
    found->second->AddFighter(fighter);
}

void GameController::UpdateRound() {
    RoundStepRespawn();
    RoundStepMove();
    RoundStepCombat();
    RoundStepDeath();
}

void GameController::RoundStepRespawn() {
    for (Fighter* p : allFighters) {
        if (p->IsDead() && !IsPositionTaken(p->GetX(), p->GetY())) {
            p->Revive();
        }
    }
}

void GameController::MoveTeam(Constants::FighterType team) {
    int nextTeam = team + 1;
    // Wrap around with modulo
    nextTeam %= Constants::FighterType::TeamCount;

    auto firstTeam = gameTeams.find(team);

    if (firstTeam == gameTeams.end()) {
        return;
    }

    std::vector<GameTeam*> enemyTeams;
    for (auto kvp : gameTeams) {
        if (kvp.first != team) {
            enemyTeams.push_back(kvp.second);
        }
    }


    firstTeam->second->MoveTowards(enemyTeams);
}

void GameController::RoundStepMove() {
    // The teams always move towards their enemies
    for (int iter = Constants::FighterType::Rock; 
        iter <= Constants::FighterType::TeamCount;
        iter++) {
        MoveTeam((Constants::FighterType)iter);
    }
}

void GameController::RoundStepCombat() {
    // Here we specifically want to attack next team
    // Paper doesn't attack scissor, etc
    for (int iter = Constants::FighterType::Rock;
            iter <= Constants::FighterType::TeamCount;
            iter++) {
        auto team = gameTeams.find((Constants::FighterType)iter);
        int otherTeamIndex = (iter - 1);
        if (otherTeamIndex < 0)
            otherTeamIndex = Constants::FighterType::TeamCount;
        auto otherTeam = gameTeams.find((Constants::FighterType(otherTeamIndex)));
        if (team != gameTeams.end() && otherTeam != gameTeams.end()) {
            team->second->PerformAttack(otherTeam->second);
        }
    }
}

int GameController::GetWinningTeam() {
    int teamId = -1;
    int maxScore = 0;
    for (auto kvp : gameTeams) {
        int score = kvp.second->GetPoints();
        if (score > maxScore) {
            maxScore = score;
            teamId = kvp.first;
        }
    }

    return teamId;
}

bool GameController::IsPositionTaken(int x, int y) {
    if (boardPositions.count(x) == 0) {
        return false;
    }

    auto foundY = boardPositions[x].find(y);

    return foundY != boardPositions[x].end() && foundY->second != nullptr;
}

void GameController::ClearPosition(int x, int y) {
    if (boardPositions.count(x) == 0) {
        return;
    }

    if (boardPositions[x].count(y) == 0) {
        return;
    }

    boardPositions[x][y] = nullptr;
}

void GameController::TakePosition(int x, int y, Fighter* fighter) {
    if (boardPositions.count(x) == 0) {
        boardPositions[x] = {};
    }

    auto foundY = boardPositions[x].find(y);
    if (foundY == boardPositions[x].end() || foundY->second == nullptr) {
        boardPositions[x][y] = fighter;
    }
    else {
        std::cout << "Cannot assign position! " << x << ", " << y << "\n";
    }
}

void GameController::RoundStepDeath() {
    for (Fighter* p : allFighters) {
        if (p->IsMarkedForDeath()) {
            p->Kill();
        }
    }
}