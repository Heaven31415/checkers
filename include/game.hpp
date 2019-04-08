#pragma once

#include "board.hpp"
#include "pawn.hpp"
#include "sound_player.hpp"
#include "state.hpp"

class Game : public State
{
public:
    Game();

    void handlePlayerAction(const sf::Vector2i& destination);
    void nextTurn();

    virtual void processEvent(const sf::Event& event) override;
    virtual void update() override;
    virtual void render(sf::RenderWindow& window) const override;
private:
    Board mBoard;
    Pawn* mSelected;
    bool mLock;
    Color mActualPlayerColor;
    sf::Text mTurnText;
    bool mFinished;
};