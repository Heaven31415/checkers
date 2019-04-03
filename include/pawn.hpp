#pragma once

#include "resources.hpp"

class Board;

class Pawn
{
public:
    Pawn(Resources* resources, Board* board, sf::Vector2i position, bool isLight);
    void draw(sf::RenderWindow* window);
    void select(bool decision);
    void move(sf::Vector2i dest);
    bool canMove(sf::Vector2i dest);
    bool canFight(sf::Vector2i dest);
    bool canFight();
    void fight(sf::Vector2i dest);

    bool isLight() { return mIsLight; }
    bool isKing() { return mIsKing; }
    sf::Vector2i getPosition() { return mPosition; }

private:
    Resources* mResources;
    Board* mBoard;
    sf::Sprite mSprite;
    sf::Vector2i mPosition;
    bool mIsLight;
    bool mIsKing;
    bool mIsSelected;
};