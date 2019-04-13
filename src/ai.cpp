#include "ai.hpp"

void ai::Pawn::move(const std::vector<ai::Pawn>& pawns, const sf::Vector2i& destination)
{
    return;
}

bool ai::Pawn::canMove(const std::vector<ai::Pawn>& pawns, const sf::Vector2i& destination) const
{
    return false;
}

std::vector<sf::Vector2i> ai::Pawn::getMovePositions(const std::vector<ai::Pawn>& pawns) const
{
    return std::vector<sf::Vector2i>{};
}

void ai::Pawn::fight(std::vector<ai::Pawn>& pawns, const sf::Vector2i& destination)
{
    return;
}

bool ai::Pawn::canFight(const std::vector<ai::Pawn>& pawns, const sf::Vector2i& destination) const
{
    return false;
}

std::vector<sf::Vector2i> ai::Pawn::getFightPositions(const std::vector<ai::Pawn>& pawns) const
{
    return std::vector<sf::Vector2i>{};
}

/*
    Spójrz na pionki znajdujące się w *board*. Wygeneruj ich
    wszystkie możliwe ruchy. Następnie dla każdego możliwego ruchu
    skopiuj *board*, wykonaj na nim dany ruch, a następnie dodaj go do dzieci *board*.
    Wywołaj siebie rekurencyjnie na każdym dziecku *board*, zmniejszając *depth* o 1.
*/

void ai::buildDecisionTree(ai::Board* board, Color color, int depth)
{
    if (depth == 0) return;

    for (size_t i = 0; i < board->pawns.size(); i++)
    {
        if (board->pawns[i].color != color) continue;

        auto movePositions = board->pawns[i].getMovePositions(board->pawns);

        for (const auto& movePosition : movePositions)
        {
            auto child = std::make_unique<ai::Board>();
            child->pawns.assign(board->pawns.begin(), board->pawns.end());
            child->pawns[i].move(child->pawns, movePosition);

            board->children.push_back(std::move(child));
        }

        auto fightPositions = board->pawns[i].getFightPositions(board->pawns);

        for (const auto& fightPosition : fightPositions)
        {
            auto child = std::make_unique<ai::Board>();
            child->pawns.assign(board->pawns.begin(), board->pawns.end());
            child->pawns[i].fight(child->pawns, fightPosition);

            board->children.push_back(std::move(child));
        }
    }

    for (const auto& child : board->children)
        ai::buildDecisionTree(child.get(), color == Color::Light ? Color::Dark : Color::Light, depth - 1);
}
