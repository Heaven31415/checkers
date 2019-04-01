#pragma once

#include "common.hpp"

class Board;

class Pawn
{
public:
    Pawn(Board* board, int playerID, sf::Vector2i position);
    void draw(sf::RenderWindow& window);
    void select(bool decision);
    void move(sf::Vector2i dest);
    bool canMove(sf::Vector2i dest);
    bool canFight(sf::Vector2i dest);
    void fight(sf::Vector2i dest);

    int playerID() { return mPlayerID; }
    sf::Vector2i position() { return mPosition; }
    bool isKing() { return mIsKing; }

private:
    Board* mBoard;
    int mPlayerID;
    sf::CircleShape mShape;
    sf::Vector2i mPosition;
    bool mIsKing;
    bool mIsSelected;
};