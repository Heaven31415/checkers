#pragma once

#include "pawn.hpp"

class Board
{
public:
    Board(Resources* resources);
    ~Board();

    void draw(sf::RenderWindow* window);
    Pawn* getPawn(sf::Vector2i position);
    void killPawn(sf::Vector2i position);
    bool isFightPossible(bool lightColor);

private:
    Resources* mResources;
    sf::Sprite mBackground;
    std::vector<Pawn*> mPawns;
};