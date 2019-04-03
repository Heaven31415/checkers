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

    void handleEvents();
    void render();
    void run();

private:
    sf::RenderWindow mWindow;
    Resources mResources;
    SoundPlayer mSoundPlayer;
    Board mBoard;

    Pawn* mSelected;
    bool mLightPlayerTurn;
    sf::Text mTurnText;
};