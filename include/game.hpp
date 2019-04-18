#pragma once

#include "ai.hpp"
#include "board.hpp"
#include "pawn.hpp"
#include "sound_player.hpp"
#include "state.hpp"

#include <iostream>

class Game : public State
{
public:
    Game();

    void handlePlayerAction(const sf::Vector2i& destination);
    Pawn* handleEnemyAction();
    void nextTurn();
    void tryToFinish();

    virtual void activation() override;
    virtual void deactivation() override;
    virtual void processEvent(const sf::Event& event) override;
    virtual void update(sf::Time dt) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    Board mBoard;
    Pawn* mSelected;
    bool mLock;
    bool mTraining;
    Color mPlayerColor;
    Color mActualPlayerColor;
    int mSearchDepth;
    sf::Time mEnemyTimer;
    sf::Text mTurnText;
    bool mFinished;
};