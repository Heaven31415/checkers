#include "ai.hpp"

void ai::Pawn::move(ai::Board* board, const sf::Vector2i& destination)
{
    return;
}

bool ai::Pawn::canMove(ai::Board* board, const sf::Vector2i& destination) const
{
    return false;
}

std::vector<sf::Vector2i> ai::Pawn::getMovePositions(ai::Board* board) const
{
    return std::vector<sf::Vector2i>{};
}

void ai::Pawn::fight(ai::Board* board, const sf::Vector2i& destination)
{
    return;
}

bool ai::Pawn::canFight(ai::Board* board, const sf::Vector2i& destination) const
{
    return false;
}

bool ai::Pawn::canFight(ai::Board* board) const
{
    return false;
}

std::vector<sf::Vector2i> ai::Pawn::getFightPositions(ai::Board* board) const
{
    return std::vector<sf::Vector2i>{};
}

void ai::buildDecisionTree(ai::Board* board, Color color, int depth)
{
    if (depth == 0) return;

    for (size_t i = 0; i < board->pawns.size(); i++)
    {
        if (board->pawns[i].color != color) continue;

        auto movePositions = board->pawns[i].getMovePositions(board);

        for (const auto& movePosition : movePositions)
        {
            auto child = std::make_unique<ai::Board>();
            child->pawns.assign(board->pawns.begin(), board->pawns.end());
            child->pawns[i].move(child.get(), movePosition);

            board->children.push_back(std::move(child));
        }

        auto fightPositions = board->pawns[i].getFightPositions(board);

        for (const auto& fightPosition : fightPositions)
        {
            auto child = std::make_unique<ai::Board>();
            child->pawns.assign(board->pawns.begin(), board->pawns.end());
            child->pawns[i].fight(child.get(), fightPosition);

            Pawn& pawn = child->pawns[i];

            /*
                TODO: This snippet doesn't handle situations in which after a first
                fight, you can fight again and choose between more than one fight.
            */
            while (pawn.canFight(child.get()))
            {
                pawn.fight(child.get(), pawn.getFightPositions(child.get())[0]);
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
