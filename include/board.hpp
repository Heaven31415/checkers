#pragma once

#include "pawn.hpp"

class Board
{
public:
    Board();
    Board(std::vector<Pawn*> pawns);
    ~Board();

    void draw(sf::RenderWindow* window);
    Pawn* getPawn(sf::Vector2i position);
    void killPawn(sf::Vector2i position);
    bool isFightPossible(bool lightColor);
    int pawnCount(bool lightColor);

private:
    sf::Sprite mBackground;
    std::vector<Pawn*> mPawns;
};