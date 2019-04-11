#pragma once

#include <memory>
#include "pawn.hpp"

#define ADD_LIGHT_PAWN(x, y) mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{x, y}, Color::Light));
#define ADD_DARK_PAWN(x, y) mPawns.push_back(std::make_unique<Pawn>(this, sf::Vector2i{x, y}, Color::Dark));

class Board : public sf::Drawable
{
public:
    Board();

    Pawn* getPawn(int x, int y) const;
    Pawn* getPawn(const sf::Vector2i& position) const;
    std::vector<Pawn*> getPawns(Color color) const;
    void killPawn(const sf::Vector2i& position);
    bool isFightPossible(Color color) const;
    bool isMovePossible(Color color) const;
    int pawnCount(Color color) const;
    void reset();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite mSprite;
    std::vector<std::unique_ptr<Pawn>> mPawns;
};