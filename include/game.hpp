#pragma once

#include "board.hpp"
#include "pawn.hpp"
#include "sound_player.hpp"

class Game
{
public:
    Game();

    void handlePlayerAction(sf::Vector2i dest);
    void nextTurn();
    void tryToFinish();

    void handleEvents();
    void render();
    void run();
private:
    sf::RenderWindow mWindow;
    Board mBoard;

    Pawn* mSelected;
    Color mActualPlayerColor;
    sf::Text mTurnText;
    bool mFinished;
};