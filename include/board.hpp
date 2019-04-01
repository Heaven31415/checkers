#pragma once

#include "pawn.hpp"

class Board
{
public:
    Board();
    void draw(sf::RenderWindow& window);
    Pawn* getPawn(sf::Vector2i position);
    void killPawn(sf::Vector2i position);

private:
    std::vector<sf::RectangleShape> mGrid;
    std::vector<Pawn> mPawns;
};