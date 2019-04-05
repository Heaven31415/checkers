#pragma once

#include <memory>
#include "pawn.hpp"

class Board : public sf::Drawable
{
public:
    Board();

    Pawn* getPawn(int x, int y);
    Pawn* getPawn(const sf::Vector2i& position);
    void killPawn(const sf::Vector2i& position);
    bool isFightPossible(Color color) const;
    int pawnCount(Color color) const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite mBackground;
    std::vector<std::unique_ptr<Pawn>> mPawns;
};