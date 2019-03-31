#pragma once

#include "pawn.hpp"

class Board
{
public:
    Board();
    void draw(sf::RenderWindow& window);
    Pawn* getPawn(sf::Vector2i pos);
    void killPawn(sf::Vector2i pos);

private:
    std::vector<sf::RectangleShape> mElements;
    std::vector<Pawn> mPawns;
};