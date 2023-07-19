#pragma once

#include "Constants.h"

class GameController;

class Fighter
{
public:
    Fighter(GameController* game, Constants::FighterType fightType, int x, int y) {
        gameControl = game;
        fighterType = fightType;
        startX = x;
        startY = y;
        currentX = startX;
        currentY = startY;
    }

    void MarkForDeath();
    void Kill();
    inline Constants::FighterType GetFighterType() { return fighterType; }

    inline bool IsMarkedForDeath() { return goingToDie; }
    inline bool IsDead() { return isDead; }

    inline int GetX() {return currentX;}
    inline int GetY() {return currentY;}
    void Revive();

    std::string GetDisplayString();

    void Move(int xIncrement, int yIncrement);
private:
    // Make the private constructor private to force initialization
    Fighter() {

    }

    GameController* gameControl;

    bool goingToDie = false;
    bool isDead = false;
    int startX = 0;
    int startY = 0;

    int currentX = 0;
    int currentY = 0;

    Constants::FighterType fighterType;
};

