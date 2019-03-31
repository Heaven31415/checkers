#include "board.hpp"

Board::Board()
: mElements{}
, mPawns{}
{
    bool light = true;

    for (size_t y = 0; y < 8; y++)
    {
        for (size_t x = 0; x < 8; x++)
        {
            sf::RectangleShape element{ {64, 64} };
            element.setPosition(x * 64.f, y * 64.f);

            if (light)
                element.setFillColor(sf::Color{ 136, 167, 216 });
            else
                element.setFillColor(sf::Color{ 37, 67, 114 });

            light = !light;

            mElements.push_back(element);
        }

        light = !light;
    }

    // Light Pawns
    mPawns.push_back(Pawn{ this, LightPlayerID, LightColor, {1, 0} });
    mPawns.push_back(Pawn{ this, LightPlayerID, LightColor, {3, 0} });
    mPawns.push_back(Pawn{ this, LightPlayerID, LightColor, {5, 0} });
    mPawns.push_back(Pawn{ this, LightPlayerID, LightColor, {7, 0} });
    mPawns.push_back(Pawn{ this, LightPlayerID, LightColor, {0, 1} });
    mPawns.push_back(Pawn{ this, LightPlayerID, LightColor, {2, 1} });
    mPawns.push_back(Pawn{ this, LightPlayerID, LightColor, {4, 1} });
    mPawns.push_back(Pawn{ this, LightPlayerID, LightColor, {6, 1} });
    mPawns.push_back(Pawn{ this, LightPlayerID, LightColor, {1, 2} });
    mPawns.push_back(Pawn{ this, LightPlayerID, LightColor, {3, 2} });
    mPawns.push_back(Pawn{ this, LightPlayerID, LightColor, {5, 2} });
    mPawns.push_back(Pawn{ this, LightPlayerID, LightColor, {7, 2} });

    // Dark Pawns
    mPawns.push_back(Pawn{ this, DarkPlayerID, DarkColor, {0, 5} });
    mPawns.push_back(Pawn{ this, DarkPlayerID, DarkColor, {2, 5} });
    mPawns.push_back(Pawn{ this, DarkPlayerID, DarkColor, {4, 5} });
    mPawns.push_back(Pawn{ this, DarkPlayerID, DarkColor, {6, 5} });
    mPawns.push_back(Pawn{ this, DarkPlayerID, DarkColor, {1, 6} });
    mPawns.push_back(Pawn{ this, DarkPlayerID, DarkColor, {3, 6} });
    mPawns.push_back(Pawn{ this, DarkPlayerID, DarkColor, {5, 6} });
    mPawns.push_back(Pawn{ this, DarkPlayerID, DarkColor, {7, 6} });
    mPawns.push_back(Pawn{ this, DarkPlayerID, DarkColor, {0, 7} });
    mPawns.push_back(Pawn{ this, DarkPlayerID, DarkColor, {2, 7} });
    mPawns.push_back(Pawn{ this, DarkPlayerID, DarkColor, {4, 7} });
    mPawns.push_back(Pawn{ this, DarkPlayerID, DarkColor, {6, 7} });
}

void Board::draw(sf::RenderWindow& window)
{
    for (size_t i = 0; i < mElements.size(); i++)
        window.draw(mElements[i]);

    for (size_t i = 0; i < mPawns.size(); i++)
        mPawns[i].draw(window);

}

Pawn* Board::getPawn(sf::Vector2i pos)
{
    if (pos.x < 0 || pos.x > 7) return nullptr;

    if (pos.y < 0 || pos.y > 7) return nullptr;

    for (size_t i = 0; i < mPawns.size(); i++)
    {
        if (mPawns[i].position() == pos)
            return &mPawns[i];
    }

    return nullptr;
}

void Board::killPawn(sf::Vector2i pos)
{
    for (size_t i = 0; i < mPawns.size(); i++)
    {
        if (mPawns[i].position() == pos)
        {
            mPawns.erase(mPawns.begin() + i);
            break;
        }
    }
}
