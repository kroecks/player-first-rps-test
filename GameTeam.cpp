#include "GameTeam.h"
#include "Fighter.h"

#include <iostream>

void GameTeam::AddPoints(int increment) {
    currentScore += increment;
}

void GameTeam::AddFighter(Fighter* fighter) {
    teamFighters.push_back(fighter);
}

// For each player on the team, find the closest player on the other team and move towards them
// This is horribly inefficient. It'd be nice if we had a means of looking up 
void GameTeam::MoveTowards(std::vector<GameTeam*> otherTeams) {
    for (auto p : teamFighters) {
        // Update this fighter to move towards another player
        Fighter* closest = nullptr;
        int currentDistance = 0;
        for (auto other : otherTeams) {
            for (auto otherFighter : other->GetAllFighters()) {
                int curDistance = (otherFighter->GetX() - p->GetX()) + (otherFighter->GetY() - p->GetY());
                if (closest == nullptr || abs(curDistance) < currentDistance) {
                    currentDistance = abs(curDistance);
                    closest = otherFighter;
                }
            }
        }
        
        if (closest != nullptr) {
            int beforeX = p->GetX();
            int beforeY = p->GetY();

            p->Move(closest->GetX() > p->GetX() ? 1 : -1,
                closest->GetY() > p->GetY() ? 1 : -1);
        }
    }
}

void GameTeam::PerformAttack(GameTeam* other) {
    for (auto p : teamFighters) {
        // For every fighter on the enemy team, check position and kill if within range
        for (auto otherFighter : other->GetAllFighters()) {
            int xDelta = abs((otherFighter->GetX() - p->GetX()));
            int yDelta = abs(otherFighter->GetY() - p->GetY());

            if (xDelta <= 1 && yDelta <= 1) {
                std::cout << "Fighter " << p->GetDisplayString() << " kills " << otherFighter->GetDisplayString() << "\n";
                otherFighter->MarkForDeath();
                AddPoints(1);
            }
        }
    }
}
