#include "Fighter.h"
#include "GameController.h"

#include <format>
#include <string>
#include <string_view>
#include <iostream>

void Fighter::MarkForDeath() {
    goingToDie = true;
}

void Fighter::Kill() {
    currentX = startX;
    currentY = startY;
    goingToDie = false;
    isDead = true;
}

void Fighter::Revive() {
    std::cout << "Fighter " << GetDisplayString() << " Revives\n";
    goingToDie = false;
    isDead = false;
}

void Fighter::Move(int xInc, int yInc) {
    int newX = currentX + xInc;
    int newY = currentY + yInc;
    if (!gameControl->IsPositionTaken(newX, newY)) {
        gameControl->TakePosition(newX, newY, this);
        gameControl->ClearPosition(currentX, currentY);
        currentX = newX;
        currentY = newY;
    }
}

std::string Fighter::GetDisplayString() {
    return "[" + Constants::FighterTypeToDisplay(GetFighterType()) + " pos=" + std::to_string(GetX()) + ", " + std::to_string(GetY()) + "]";
}