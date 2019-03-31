#include "pawn.hpp"
#include "board.hpp"

Pawn::Pawn(Board* board, int playerID, sf::Color color, sf::Vector2i position)
: mBoard{ board }
, mPlayerID{ playerID }
, mColor{ color }
, mShape{ 24.f }
, mPosition{ position }
, mIsKing{ false }
, mIsSelected{ false }
{
    mShape.setFillColor(mColor);
    mShape.setOutlineColor(mColor + sf::Color(50, 50, 50));
    mShape.setOutlineThickness(2.f);
    mShape.setOrigin(24.f, 24.f);
    mShape.setPosition(64.f * position.x + 32.f, 64.f * position.y + 32.f);
}

void Pawn::draw(sf::RenderWindow& window)
{
    window.draw(mShape);
}

void Pawn::select(bool decision)
{
    if (decision)
        mShape.setFillColor(mColor + sf::Color(50, 50, 50));
    else
        mShape.setFillColor(mColor);

    mIsSelected = decision;
}

void Pawn::move(sf::Vector2i pos)
{
    mPosition = pos;
    mShape.setPosition(64.f * pos.x + 32.f, 64.f * pos.y + 32.f);
}

bool Pawn::canMove(sf::Vector2i pos)
{
    if (pos == mPosition) return false;

    // TODO: Handle me in the future
    if (mIsKing) return false;

    if (mColor == LightColor)
    {
        if (pos.y == mPosition.y + 1 && (pos.x == mPosition.x - 1 || pos.x == mPosition.x + 1))
        {
            if (mBoard->getPawn(pos))
                return false;
            else
                return true;
        }

        return false;
    }
    else
    {
        if (pos.y == mPosition.y - 1 && (pos.x == mPosition.x - 1 || pos.x == mPosition.x + 1))
        {
            if (mBoard->getPawn(pos))
                return false;
            else
                return true;
        }

        return false;
    }

    return false;
}

sf::Vector2i Pawn::canFight(sf::Vector2i pos)
{
    if (pos == mPosition) return {};

    // TODO: Handle me in the future
    if (mIsKing) return {};

    if (pos.x == mPosition.x + 2 && pos.y == mPosition.y + 2 )
    {
        Pawn* pawn = mBoard->getPawn({ mPosition.x + 1, mPosition.y + 1 });
        if (pawn && pawn->playerID() != mPlayerID)
            return pawn->position();
        else return {};
    }
    else if (pos.x == mPosition.x - 2 && pos.y == mPosition.y + 2)
    {
        Pawn* pawn = mBoard->getPawn({ mPosition.x - 1, mPosition.y + 1 });
        if (pawn && pawn->playerID() != mPlayerID)
            return pawn->position();
        else return {};
    }
    else if (pos.x == mPosition.x + 2 && pos.y == mPosition.y - 2)
    {
        Pawn* pawn = mBoard->getPawn({ mPosition.x + 1, mPosition.y - 1 });
        if (pawn && pawn->playerID() != mPlayerID)
            return pawn->position();
        else return {};
    }
    else if (pos.x == mPosition.x - 2 && pos.y == mPosition.y - 2)
    {
        Pawn* pawn = mBoard->getPawn({ mPosition.x - 1, mPosition.y - 1 });
        if (pawn && pawn->playerID() != mPlayerID)
            return pawn->position();
        else return {};
    }
    
    return {};
}
