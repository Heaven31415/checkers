#include "board.hpp"

Board::Board()
: mBackground{Resources::getTexture("Board")}
, mPawns{}
{
    mPawns.reserve(24);

    // Light Pawns
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 1, 0 }, Color::Light));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 3, 0 }, Color::Light));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 5, 0 }, Color::Light));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 7, 0 }, Color::Light));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 0, 1 }, Color::Light));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 2, 1 }, Color::Light));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 4, 1 }, Color::Light));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 6, 1 }, Color::Light));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 1, 2 }, Color::Light));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 3, 2 }, Color::Light));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 5, 2 }, Color::Light));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 7, 2 }, Color::Light));

    // Dark Pawns
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 0, 5 }, Color::Dark));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 2, 5 }, Color::Dark));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 4, 5 }, Color::Dark));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 6, 5 }, Color::Dark));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 1, 6 }, Color::Dark));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 3, 6 }, Color::Dark));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 5, 6 }, Color::Dark));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 7, 6 }, Color::Dark));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 0, 7 }, Color::Dark));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 2, 7 }, Color::Dark));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 4, 7 }, Color::Dark));
    mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{ 6, 7 }, Color::Dark));
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mBackground, states);
    for (const auto& pawn : mPawns) target.draw(*pawn, states);
}

Pawn* Board::getPawn(int x, int y)
{
    if (x < 0 || x >= 8) return nullptr;

    if (y < 0 || y >= 8) return nullptr;

    for (const auto& pawn : mPawns)
        if (pawn->getPosition() == sf::Vector2i{x, y}) return pawn.get();

    return nullptr;
}

Pawn* Board::getPawn(const sf::Vector2i& position)
{
    return getPawn(position.x, position.y);
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

bool Board::isFightPossible(Color color) const
{
    for (const auto& pawn : mPawns)
        if (pawn->getColor() == color && pawn->canFight())
            return true;

    return false;
}

int Board::pawnCount(Color color) const
{
    int count{ 0 };

    for (const auto& pawn : mPawns)
        if (pawn->getColor() == color)
            count++;

    return count;
}
