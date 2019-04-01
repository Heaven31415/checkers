#include "pawn.hpp"
#include "board.hpp"

Pawn::Pawn(Board* board, int playerID, sf::Vector2i position)
: mBoard{ board }
, mPlayerID{ playerID }
, mShape{ PAWN_RADIUS }
, mPosition{ position }
, mIsKing{ false }
, mIsSelected{ false }
{
    if (mPlayerID == LIGHT_PLAYER_ID)
    {
        mShape.setFillColor(LIGHT_PAWN_COLOR);
        mShape.setOutlineColor(LIGHT_PAWN_COLOR + sf::Color{ 50, 50, 50 });
    }
    else // mPlayerID == DARK_PLAYER_ID
    {
        mShape.setFillColor(DARK_PAWN_COLOR);
        mShape.setOutlineColor(DARK_PAWN_COLOR + sf::Color{ 50, 50, 50 });
    }

    mShape.setOutlineThickness(2.f);
    mShape.setOrigin(PAWN_RADIUS, PAWN_RADIUS);
    mShape.setPosition(UNIT_SIZE * position.x + UNIT_SIZE / 2.f, UNIT_SIZE * position.y + UNIT_SIZE / 2.f);
}

void Pawn::draw(sf::RenderWindow& window)
{
    window.draw(mShape);
}

void Pawn::select(bool decision)
{
    if (decision)
    {
        if(mPlayerID == LIGHT_PLAYER_ID)
            mShape.setFillColor(LIGHT_PAWN_COLOR + sf::Color(50, 50, 50));
        else
            mShape.setFillColor(DARK_PAWN_COLOR + sf::Color(50, 50, 50));
    }
    else
    {
        if (mPlayerID == LIGHT_PLAYER_ID)
            mShape.setFillColor(LIGHT_PAWN_COLOR);
        else
            mShape.setFillColor(DARK_PAWN_COLOR);
    }

    mIsSelected = decision;
}

void Pawn::move(sf::Vector2i dest)
{
    mPosition = dest;
    mShape.setPosition(UNIT_SIZE * dest.x + UNIT_SIZE / 2.f, UNIT_SIZE * dest.y + UNIT_SIZE / 2.f);
}

bool Pawn::canMove(sf::Vector2i dest)
{
    if (dest == mPosition) return false;

    // TODO: Handle me in the future
    if (mIsKing) return false;

    if (mPlayerID == LIGHT_PLAYER_ID)
    {
        if ((dest.x == mPosition.x - 1 || dest.x == mPosition.x + 1) && (dest.y == mPosition.y + 1))
            return mBoard->getPawn(dest) == NULL;
    }
    else // mPlayerID == DARK_PLAYER_ID
    {
        if ((dest.x == mPosition.x - 1 || dest.x == mPosition.x + 1) && (dest.y == mPosition.y - 1))
            return mBoard->getPawn(dest) == NULL;
    }

    // You shouldn't be here
    return false;
}

bool Pawn::canFight(sf::Vector2i dest)
{
    if (dest == mPosition) return false;

    if (mBoard->getPawn(dest) != NULL) return false;

    // TODO: Handle me in the future
    if (mIsKing) return false;

    Pawn* enemy = NULL;

    if (dest.x == mPosition.x + 2 && dest.y == mPosition.y + 2)
        enemy = mBoard->getPawn({ mPosition.x + 1, mPosition.y + 1 });
    else if (dest.x == mPosition.x - 2 && dest.y == mPosition.y + 2)
        enemy = mBoard->getPawn({ mPosition.x - 1, mPosition.y + 1 });
    else if (dest.x == mPosition.x + 2 && dest.y == mPosition.y - 2)
        enemy = mBoard->getPawn({ mPosition.x + 1, mPosition.y - 1 });
    else if (dest.x == mPosition.x - 2 && dest.y == mPosition.y - 2)
        enemy = mBoard->getPawn({ mPosition.x - 1, mPosition.y - 1 });

    return enemy && enemy->playerID() != mPlayerID;
}

void Pawn::fight(sf::Vector2i dest)
{
    if (dest == mPosition) return;

    if (mBoard->getPawn(dest) != NULL) return;

    // TODO: Handle me in the future
    if (mIsKing) return;

    Pawn* enemy = NULL;

    if (dest.x == mPosition.x + 2 && dest.y == mPosition.y + 2)
        enemy = mBoard->getPawn({ mPosition.x + 1, mPosition.y + 1 });
    else if (dest.x == mPosition.x - 2 && dest.y == mPosition.y + 2)
        enemy = mBoard->getPawn({ mPosition.x - 1, mPosition.y + 1 });
    else if (dest.x == mPosition.x + 2 && dest.y == mPosition.y - 2)
        enemy = mBoard->getPawn({ mPosition.x + 1, mPosition.y - 1 });
    else if (dest.x == mPosition.x - 2 && dest.y == mPosition.y - 2)
        enemy = mBoard->getPawn({ mPosition.x - 1, mPosition.y - 1 });

    if (enemy && enemy->playerID() != mPlayerID)
    {
        move(dest);
        mBoard->killPawn(enemy->position());
    }
}
