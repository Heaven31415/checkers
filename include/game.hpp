#pragma once

#include "board.hpp"
#include "pawn.hpp"
#include "sound_player.hpp"

class Game
{
public:
    Game();

    void handlePlayerAction(const sf::Vector2i& destination);
    void nextTurn();

    void handleEvents();
    void render();
    void run();
private:
    sf::RenderWindow mWindow;
    Board mBoard;
    Pawn* mSelected;
    bool mLock;
    Color mActualPlayerColor;
    sf::Text mTurnText;
    bool mFinished;
};