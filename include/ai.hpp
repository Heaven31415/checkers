#pragma once

#include <memory>
#include "common.hpp"

namespace ai
{
    struct Board;

    struct Move
    {
        enum class Type
        {
            Move,
            Fight
        };

        Type type;
        sf::Vector2i start;
        sf::Vector2i end;
    };

    struct Pawn
    {
        ai::Board* board;
        sf::Vector2i position;
        Color color;
        bool isKing;

        void move(const sf::Vector2i& destination, bool duringFight = false);
        bool canMove(const sf::Vector2i& destination) const;
        bool canMove() const;
        std::vector<sf::Vector2i> getMovePositions() const;

        void fight(const sf::Vector2i& destination);
        bool canFight(const sf::Vector2i& destination) const;
        bool canFight() const;
        std::vector<sf::Vector2i> getFightPositions() const;
    };

    struct Board
    {
        ai::Board* parent;
        std::unique_ptr<Move> move;
        std::vector<ai::Pawn> pawns;
        std::vector<std::unique_ptr<ai::Board>> children;

        ai::Pawn* getPawn(int x, int y);
        ai::Pawn* getPawn(const sf::Vector2i& position);
        std::vector<ai::Pawn*> getPawns(Color color);
        void killPawn(const sf::Vector2i& position);
        bool isFightPossible(Color color) const;
        bool isMovePossible(Color color) const;
        int pawnCount(Color color) const;
    };

    void buildDecisionTree(ai::Board* board, Color color, int depth);
    int computeHeuristic(ai::Board* board);
}