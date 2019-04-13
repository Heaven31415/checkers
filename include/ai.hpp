#pragma once

#include <memory>
#include "common.hpp"

namespace ai
{
    struct Pawn
    {
        sf::Vector2i position;
        Color color;
        bool isKing;

        void move(const std::vector<ai::Pawn>& pawns, const sf::Vector2i& destination);
        bool canMove(const std::vector<ai::Pawn>& pawns, const sf::Vector2i& destination) const;
        std::vector<sf::Vector2i> getMovePositions(const std::vector<ai::Pawn>& pawns) const;

        void fight(std::vector<ai::Pawn>& pawns, const sf::Vector2i& destination);
        bool canFight(const std::vector<ai::Pawn>& pawns, const sf::Vector2i& destination) const;
        std::vector<sf::Vector2i> getFightPositions(const std::vector<ai::Pawn>& pawns) const;
    };

    struct Board
    {
        std::vector<ai::Pawn> pawns;
        std::vector<std::unique_ptr<ai::Board>> children;
    };

    void buildDecisionTree(ai::Board* board, Color color, int depth);
}