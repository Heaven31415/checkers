#pragma once

#include <memory>
#include "common.hpp"

namespace ai
{
    struct Board;

    struct Pawn
    {
        sf::Vector2i position;
        Color color;
        bool isKing;

        void move(ai::Board* board, const sf::Vector2i& destination);
        bool canMove(ai::Board* board, const sf::Vector2i& destination) const;
        std::vector<sf::Vector2i> getMovePositions(ai::Board* board) const;

        void fight(ai::Board* board, const sf::Vector2i& destination);
        bool canFight(ai::Board* board, const sf::Vector2i& destination) const;
        bool canFight(ai::Board* board) const;
        std::vector<sf::Vector2i> getFightPositions(ai::Board* board) const;
    };

    struct Board
    {
        std::vector<ai::Pawn> pawns;
        std::vector<std::unique_ptr<ai::Board>> children;
    };

    void buildDecisionTree(ai::Board* board, Color color, int depth);
    int computeHeuristic(ai::Board* board);
}