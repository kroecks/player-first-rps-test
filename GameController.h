#pragma once
#include <unordered_map>
#include "Constants.h"

class Fighter;
class GameTeam;

class GameController
{
public:
    void UpdateRound();
    int GetWinningTeam();
    void AddPlayerToGame(Fighter* fighter);
    void SetupGame();

    bool IsPositionTaken(int x, int y);
    void ClearPosition(int x, int y);
    void TakePosition(int x, int y, Fighter* fighter);
    
    void ShutDown();

private:
    
    std::unordered_map<Constants::FighterType, GameTeam*> gameTeams;
    std::vector<Fighter*> allFighters;
    std::unordered_map<int, std::unordered_map<int, Fighter*>> boardPositions;

    void MoveTeam(Constants::FighterType teamId);

    void RoundStepRespawn();
    void RoundStepMove();
    void RoundStepCombat();
    void RoundStepDeath();
};

