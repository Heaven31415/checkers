#include "pawn.hpp"
#include "board.hpp"

Pawn::Pawn(Resources* resources, Board* board, sf::Vector2i position, bool isLight)
: mResources{resources}
, mBoard{ board }
, mSprite{}
, mPosition{ position }
, mIsLight{ isLight }
, mIsKing{ false }
, mIsSelected{ false }
{
    if (mIsLight)
        mSprite.setTexture(mResources->getTexture("LightPawn"));
    else
        mSprite.setTexture(mResources->getTexture("DarkPawn"));

    move(mPosition);
}

void Pawn::draw(sf::RenderWindow* window)
{
    window->draw(mSprite);
}

void Pawn::select(bool decision)
{
    std::string textureName = "";

    if (mIsLight) textureName += "Light";
    else textureName += "Dark";

    if (mIsKing) textureName += "King";
    else textureName += "Pawn";

    if (decision) textureName += "Selected";

    mSprite.setTexture(mResources->getTexture(textureName));
    mIsSelected = decision;
}

void Pawn::move(sf::Vector2i dest)
{
    mPosition = dest;
    mSprite.setPosition(64.f * (dest.x + 5), 64.f * (dest.y + 1));

    if (!mIsKing && (mIsLight && dest.y == 7 || !mIsLight && dest.y == 0))
    {
        mIsKing = true;

        if (mIsLight)
            mSprite.setTexture(mResources->getTexture("LightKing"));
        else
            mSprite.setTexture(mResources->getTexture("DarkKing"));
    }
}

bool Pawn::canMove(sf::Vector2i dest)
{
    if (dest.x < 0 || dest.x >= 8)
        return false;

    if (dest.y < 0 || dest.y >= 8)
        return false;

    if (dest == mPosition) return false;

    if (mIsKing)
    {
        if (abs(dest.x - mPosition.x) != abs(dest.y - mPosition.y))
            return false;

        int dx = (dest.x > mPosition.x) ? 1 : -1;
        int dy = (dest.y > mPosition.y) ? 1 : -1;

        bool foundSomebody = false;

        int actualX = mPosition.x + dx;
        int actualY = mPosition.y + dy;

        while (actualX != dest.x && actualY != dest.y)
        {
            if (mBoard->getPawn({ actualX, actualY }))
            {
                foundSomebody = true;
                break;
            }

            actualX += dx; 
            actualY += dy;
        }

        return !foundSomebody && !mBoard->getPawn(dest);
    }

    if (mIsLight)
    {
        if ((dest.x == mPosition.x - 1 || dest.x == mPosition.x + 1) && (dest.y == mPosition.y + 1))
            return mBoard->getPawn(dest) == NULL;
    }
    else
    {
        if ((dest.x == mPosition.x - 1 || dest.x == mPosition.x + 1) && (dest.y == mPosition.y - 1))
            return mBoard->getPawn(dest) == NULL;
    }

    return false;
}

bool Pawn::canFight(sf::Vector2i dest)
{
    if (dest.x < 0 || dest.x >= 8)
        return false;

    if (dest.y < 0 || dest.y >= 8)
        return false;

    if (dest == mPosition) return false;

    if (mBoard->getPawn(dest) != NULL) return false;

    if (mIsKing)
    {
        if (abs(dest.x - mPosition.x) != abs(dest.y - mPosition.y))
            return false;

        int dx = (dest.x > mPosition.x) ? 1 : -1;
        int dy = (dest.y > mPosition.y) ? 1 : -1;

        int foundEnemies = 0;
        int foundAllies = 0;

        int actualX = mPosition.x + dx;
        int actualY = mPosition.y + dy;

        while (actualX != dest.x && actualY != dest.y)
        {
            Pawn* pawn = mBoard->getPawn({ actualX, actualY });
            if (pawn)
            {
                if (pawn->isLight() == mIsLight)
                    foundAllies++;
                else
                    foundEnemies++;
            }

            actualX += dx;
            actualY += dy;
        }

        return foundAllies == 0 && foundEnemies == 1 && !mBoard->getPawn(dest);
    }

    Pawn* enemy = NULL;

    if (dest.x == mPosition.x + 2 && dest.y == mPosition.y + 2)
        enemy = mBoard->getPawn({ mPosition.x + 1, mPosition.y + 1 });
    else if (dest.x == mPosition.x - 2 && dest.y == mPosition.y + 2)
        enemy = mBoard->getPawn({ mPosition.x - 1, mPosition.y + 1 });
    else if (dest.x == mPosition.x + 2 && dest.y == mPosition.y - 2)
        enemy = mBoard->getPawn({ mPosition.x + 1, mPosition.y - 1 });
    else if (dest.x == mPosition.x - 2 && dest.y == mPosition.y - 2)
        enemy = mBoard->getPawn({ mPosition.x - 1, mPosition.y - 1 });

    return enemy && enemy->isLight() != mIsLight;
}

void Pawn::fight(sf::Vector2i dest)
{
    if (dest.x < 0 || dest.x >= 8)
        return;

    if (dest.y < 0 || dest.y >= 8)
        return;

    if (dest == mPosition) return;

    if (mBoard->getPawn(dest) != NULL) return;

    if (mIsKing)
    {
        int dx = (dest.x > mPosition.x) ? 1 : -1;
        int dy = (dest.y > mPosition.y) ? 1 : -1;

        int actualX = mPosition.x + dx;
        int actualY = mPosition.y + dy;

        while (actualX != dest.x && actualY != dest.y)
        {
            Pawn* pawn = mBoard->getPawn({ actualX, actualY });
            if (pawn)
            {
                move(dest);
                mBoard->killPawn(pawn->getPosition());
                break;
            }

            actualX += dx;
            actualY += dy;
        }
    }
    else
    {
        Pawn* enemy = NULL;

        if (dest.x == mPosition.x + 2 && dest.y == mPosition.y + 2)
            enemy = mBoard->getPawn({ mPosition.x + 1, mPosition.y + 1 });
        else if (dest.x == mPosition.x - 2 && dest.y == mPosition.y + 2)
            enemy = mBoard->getPawn({ mPosition.x - 1, mPosition.y + 1 });
        else if (dest.x == mPosition.x + 2 && dest.y == mPosition.y - 2)
            enemy = mBoard->getPawn({ mPosition.x + 1, mPosition.y - 1 });
        else if (dest.x == mPosition.x - 2 && dest.y == mPosition.y - 2)
            enemy = mBoard->getPawn({ mPosition.x - 1, mPosition.y - 1 });

        if (enemy && enemy->isLight() != mIsLight)
        {
            move(dest);
            mBoard->killPawn(enemy->getPosition());
        }
    }
}
