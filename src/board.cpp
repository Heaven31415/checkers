#include "board.hpp"

Board::Board(Resources* resources)
: mResources{resources}
, mBackground{resources->getTexture("Board")}
, mPawns
{
    // Light Pawns
    { mResources, this, LIGHT_PLAYER_ID, {1, 0} },
    { mResources, this, LIGHT_PLAYER_ID, {3, 0} },
    { mResources, this, LIGHT_PLAYER_ID, {5, 0} },
    { mResources, this, LIGHT_PLAYER_ID, {7, 0} },
    { mResources, this, LIGHT_PLAYER_ID, {0, 1} },
    { mResources, this, LIGHT_PLAYER_ID, {2, 1} },
    { mResources, this, LIGHT_PLAYER_ID, {4, 1} },
    { mResources, this, LIGHT_PLAYER_ID, {6, 1} },
    { mResources, this, LIGHT_PLAYER_ID, {1, 2} },
    { mResources, this, LIGHT_PLAYER_ID, {3, 2} },
    { mResources, this, LIGHT_PLAYER_ID, {5, 2} },
    { mResources, this, LIGHT_PLAYER_ID, {7, 2} },

    // Dark Pawns
    { mResources, this, DARK_PLAYER_ID, {0, 5} },
    { mResources, this, DARK_PLAYER_ID, {2, 5} },
    { mResources, this, DARK_PLAYER_ID, {4, 5} },
    { mResources, this, DARK_PLAYER_ID, {6, 5} },
    { mResources, this, DARK_PLAYER_ID, {1, 6} },
    { mResources, this, DARK_PLAYER_ID, {3, 6} },
    { mResources, this, DARK_PLAYER_ID, {5, 6} },
    { mResources, this, DARK_PLAYER_ID, {7, 6} },
    { mResources, this, DARK_PLAYER_ID, {0, 7} },
    { mResources, this, DARK_PLAYER_ID, {2, 7} },
    { mResources, this, DARK_PLAYER_ID, {4, 7} },
    { mResources, this, DARK_PLAYER_ID, {6, 7} }
}
{

}

void Board::draw(sf::RenderWindow& window)
{
    window.draw(mBackground);

    for (size_t i = 0; i < mPawns.size(); i++)
        mPawns[i].draw(window);
}

Pawn* Board::getPawn(sf::Vector2i position)
{
    if (position.x < 0 || position.x >= BOARD_WIDTH) 
        return NULL;

    if (position.y < 0 || position.y >= BOARD_HEIGHT) 
        return NULL;

    for (size_t i = 0; i < mPawns.size(); i++)
    {
        if (mPawns[i].position() == position)
            return &mPawns[i];
    }

    return NULL;
}

void Board::killPawn(sf::Vector2i position)
{
    for (size_t i = 0; i < mPawns.size(); i++)
    {
        if (mPawns[i].position() == position)
        {
            mPawns.erase(mPawns.begin() + i);
            break;
        }
    }
}
