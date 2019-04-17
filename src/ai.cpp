#include "ai.hpp"

void ai::Pawn::move(const sf::Vector2i& destination, bool duringFight)
{
    return;
}

bool ai::Pawn::canMove(const sf::Vector2i& destination) const
{
    return false;
}

bool ai::Pawn::canMove() const
{
    return false;
}

std::vector<sf::Vector2i> ai::Pawn::getMovePositions() const
{
    return std::vector<sf::Vector2i>{};
}

void ai::Pawn::fight(const sf::Vector2i& destination)
{
    return;
}

bool ai::Pawn::canFight(const sf::Vector2i& destination) const
{
    return false;
}

bool ai::Pawn::canFight() const
{
    return false;
}

std::vector<sf::Vector2i> ai::Pawn::getFightPositions() const
{
    return std::vector<sf::Vector2i>{};
}

void ai::buildDecisionTree(ai::Board* board, Color color, int depth)
{
    if (depth == 0) return;

    for (size_t i = 0; i < board->pawns.size(); i++)
    {
        if (board->pawns[i].color != color) continue;

        auto movePositions = board->pawns[i].getMovePositions();

        for (const auto& movePosition : movePositions)
        {
            auto child = std::make_unique<ai::Board>();
            child->pawns.assign(board->pawns.begin(), board->pawns.end());
            child->pawns[i].move(movePosition);

            board->children.push_back(std::move(child));
        }

        auto fightPositions = board->pawns[i].getFightPositions();

        for (const auto& fightPosition : fightPositions)
        {
            auto child = std::make_unique<ai::Board>();
            child->pawns.assign(board->pawns.begin(), board->pawns.end());
            child->pawns[i].fight(fightPosition);

            Pawn& pawn = child->pawns[i];

            /*
                TODO: This snippet doesn't handle situations in which after a first
                fight, you can fight again and choose between more than one fight.
            */
            while (pawn.canFight())
            {
                pawn.fight(pawn.getFightPositions()[0]);
            }

            board->children.push_back(std::move(child));
        }
    }

    for (const auto& child : board->children)
        ai::buildDecisionTree(child.get(), color == Color::Light ? Color::Dark : Color::Light, depth - 1);
}

int ai::computeHeuristic(ai::Board* board)
{
    return 0;
}
