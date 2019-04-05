#pragma once

#include "resources.hpp"

class Board;

class Pawn : public sf::Drawable
{
public:
    Pawn(Board* board, const sf::Vector2i& position, bool isLight);
    void select(bool decision);
    void move(const sf::Vector2i& dest);
    bool canMove(const sf::Vector2i& dest);
    bool canFight(const sf::Vector2i& dest);
    bool canFight();
    void fight(const sf::Vector2i& dest);

    bool isLight() { return mIsLight; }
    bool isKing() { return mIsKing; }
    const sf::Vector2i& getPosition() { return mPosition; }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Board* mBoard;
    sf::Sprite mSprite;
    sf::Vector2i mPosition;
    bool mIsLight;
    bool mIsKing;
    bool mIsSelected;
};