#include "board.hpp"

Board::Board()
: mGrid{}
, mPawns
{
    // Light Pawns
    { this, LIGHT_PLAYER_ID, {1, 0} },
    { this, LIGHT_PLAYER_ID, {3, 0} },
    { this, LIGHT_PLAYER_ID, {5, 0} },
    { this, LIGHT_PLAYER_ID, {7, 0} },
    { this, LIGHT_PLAYER_ID, {0, 1} },
    { this, LIGHT_PLAYER_ID, {2, 1} },
    { this, LIGHT_PLAYER_ID, {4, 1} },
    { this, LIGHT_PLAYER_ID, {6, 1} },
    { this, LIGHT_PLAYER_ID, {1, 2} },
    { this, LIGHT_PLAYER_ID, {3, 2} },
    { this, LIGHT_PLAYER_ID, {5, 2} },
    { this, LIGHT_PLAYER_ID, {7, 2} },

    // Dark Pawns
    { this, DARK_PLAYER_ID, {0, 5} },
    { this, DARK_PLAYER_ID, {2, 5} },
    { this, DARK_PLAYER_ID, {4, 5} },
    { this, DARK_PLAYER_ID, {6, 5} },
    { this, DARK_PLAYER_ID, {1, 6} },
    { this, DARK_PLAYER_ID, {3, 6} },
    { this, DARK_PLAYER_ID, {5, 6} },
    { this, DARK_PLAYER_ID, {7, 6} },
    { this, DARK_PLAYER_ID, {0, 7} },
    { this, DARK_PLAYER_ID, {2, 7} },
    { this, DARK_PLAYER_ID, {4, 7} },
    { this, DARK_PLAYER_ID, {6, 7} }
}
{
    bool lightColor = true;

    for (size_t y = 0; y < BOARD_HEIGHT; y++)
    {
        for (size_t x = 0; x < BOARD_WIDTH; x++)
        {
            sf::RectangleShape fragment{};
            fragment.setSize({ UNIT_SIZE, UNIT_SIZE });
            fragment.setPosition(x * UNIT_SIZE, y * UNIT_SIZE);

            if (lightColor)
                fragment.setFillColor(LIGHT_GRID_COLOR);
            else
                fragment.setFillColor(DARK_GRID_COLOR);

            lightColor = !lightColor;

            mGrid.push_back(fragment);
        }

        lightColor = !lightColor;
    }
}

void Board::draw(sf::RenderWindow& window)
{
    for (size_t i = 0; i < mGrid.size(); i++)
        window.draw(mGrid[i]);

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
