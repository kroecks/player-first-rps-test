#pragma once
#include <vector>

class Fighter;
class GameController;

class GameTeam
{
public:
    GameTeam(GameController* control) {
        gameControl = control;
    }

    void Respawn();
    void AddPoints(int numPoints);
    inline int GetPoints() { return currentScore; }
    
    void AddFighter(Fighter* newFighter);

    inline const std::vector<Fighter*> GetAllFighters() {
        return teamFighters;
    }

    void MoveTowards(std::vector<GameTeam*> otherTeams);
    void PerformAttack(GameTeam* otherTeam);

private:
    GameController* gameControl;
    int currentScore = 0;

    std::vector<Fighter*> teamFighters;
};

