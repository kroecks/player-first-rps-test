#pragma once
#include <vector>

class Fighter;

class BoardTile
{
public:
    bool IsOccupied();
    Fighter* GetFighter();
private:
    Fighter* currentFighter;

    std::vector<BoardTile*> adjacentTiles;
};

