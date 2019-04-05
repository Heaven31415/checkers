#include "board.hpp"

Board::Board()
: mBackground{Resources::getTexture("Board")}
, mPawns{}
{
    mPawns.reserve(24);

    // Light Pawns
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 1, 0 }, true));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 3, 0 }, true));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 5, 0 }, true));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 7, 0 }, true));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 0, 1 }, true));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 2, 1 }, true));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 4, 1 }, true));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 6, 1 }, true));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 1, 2 }, true));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 3, 2 }, true));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 5, 2 }, true));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 7, 2 }, true));

    // Dark Pawns
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 0, 5 }, false));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 2, 5 }, false));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 4, 5 }, false));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 6, 5 }, false));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 1, 6 }, false));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 3, 6 }, false));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 5, 6 }, false));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 7, 6 }, false));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 0, 7 }, false));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 2, 7 }, false));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 4, 7 }, false));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 6, 7 }, false));
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mBackground, states);
    // TODO: Add pawn drawing after Pawn refactor
}

Pawn* Board::getPawn(const sf::Vector2i& position)
{
    if (position.x < 0 || position.x >= 8) return nullptr;

    if (position.y < 0 || position.y >= 8) return nullptr;

    for (const auto& pawn : mPawns)
        if (pawn->getPosition() == position) return pawn.get();

    return nullptr;
}

void Board::killPawn(const sf::Vector2i& position)
{
    mPawns.erase(
        std::remove_if(
            mPawns .begin(),
            mPawns.end(),
            [&position](const std::unique_ptr<Pawn>& pawn) { return pawn->getPosition() == position; }
        ),
        mPawns.end()
    );
}

bool Board::isFightPossible(bool lightColor) const
{
    for (const auto& pawn : mPawns)
        if (pawn->isLight() == lightColor && pawn->canFight())
            return true;

    return false;
}

int Board::pawnCount(bool lightColor) const
{
    int count{ 0 };

    for (const auto& pawn : mPawns)
        if (pawn->isLight() == lightColor)
            count++;

    return count;
}
