#include "board.hpp"

Board::Board(Resources* resources)
: mResources{resources}
, mBackground{resources->getTexture("Board")}
, mPawns
{
    // Light Pawns
    new Pawn{ mResources, this, {1, 0}, true },
    new Pawn{ mResources, this, {3, 0}, true },
    new Pawn{ mResources, this, {5, 0}, true },
    new Pawn{ mResources, this, {7, 0}, true },
    new Pawn{ mResources, this, {0, 1}, true},
    new Pawn{ mResources, this, {2, 1}, true },
    new Pawn{ mResources, this, {4, 1}, true },
    new Pawn{ mResources, this, {6, 1}, true },
    new Pawn{ mResources, this, {1, 2}, true },
    new Pawn{ mResources, this, {3, 2}, true },
    new Pawn{ mResources, this, {5, 2}, true },
    new Pawn{ mResources, this, {7, 2}, true },

    // Dark Pawns
    new Pawn{ mResources, this, {0, 5}, false },
    new Pawn{ mResources, this, {2, 5}, false },
    new Pawn{ mResources, this, {4, 5}, false },
    new Pawn{ mResources, this, {6, 5}, false },
    new Pawn{ mResources, this, {1, 6}, false },
    new Pawn{ mResources, this, {3, 6}, false },
    new Pawn{ mResources, this, {5, 6}, false },
    new Pawn{ mResources, this, {7, 6}, false },
    new Pawn{ mResources, this, {0, 7}, false },
    new Pawn{ mResources, this, {2, 7}, false },
    new Pawn{ mResources, this, {4, 7}, false },
    new Pawn{ mResources, this, {6, 7}, false }
}
{
}

Board::~Board()
{
    for (size_t i = 0; i < mPawns.size(); i++)
        delete mPawns[i];
}

void Board::draw(sf::RenderWindow* window)
{
    window->draw(mBackground);

    for (size_t i = 0; i < mPawns.size(); i++)
        mPawns[i]->draw(window);
}

Pawn* Board::getPawn(sf::Vector2i position)
{
    if (position.x < 0 || position.x >= 8) 
        return NULL;

    if (position.y < 0 || position.y >= 8) 
        return NULL;

    for (size_t i = 0; i < mPawns.size(); i++)
    {
        if (mPawns[i]->getPosition() == position)
            return mPawns[i];
    }

    return NULL;
}

void Board::killPawn(sf::Vector2i position)
{
    for (size_t i = 0; i < mPawns.size(); i++)
    {
        if (mPawns[i]->getPosition() == position)
        {
            delete mPawns[i];
            mPawns.erase(mPawns.begin() + i);
            break;
        }
    }
}

bool Board::isFightPossible(bool lightColor)
{
    for (size_t i = 0; i < mPawns.size(); i++)
    {
        if (mPawns[i]->isLight() == lightColor && mPawns[i]->canFight())
            return true;
    }

    return false;
}
