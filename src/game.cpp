#include "game.hpp"

Game::Game()
: mWindow{sf::VideoMode{896, 640}, "Checkers"}
, mResources{}
, mSoundPlayer{&mResources}
, mBoard{&mResources}
, mSelected{NULL}
, mLightPlayerTurn{true}
, mTurnText{"Light Player Turn", mResources.getFont(), 30}
, mFinished{false}
{
    mWindow.setFramerateLimit(60);
    
    sf::FloatRect rect = mTurnText.getLocalBounds();
    mTurnText.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
    mTurnText.setPosition(160.f, 64.f);
}

void Game::handlePlayerAction(sf::Vector2i dest)
{
    bool fightPossible = mBoard.isFightPossible(mLightPlayerTurn);

    if (!mSelected)
    {
        mSelected = mBoard.getPawn(dest);
        if (mSelected && mSelected->isLight() == mLightPlayerTurn && (!fightPossible || (fightPossible && mSelected->canFight())))
            mSelected->select(true);
        else
        {
            mSelected = NULL;
            mSoundPlayer.playSound("Impossible", 10, 1.2f);
        }
    }
    else
    {
        if (mSelected->canMove(dest))
        {
            mSelected->select(false);
            mSelected->move(dest);
            mSelected = NULL;
            nextTurn();
            mSoundPlayer.playSound("Move", 20, 1.2f);
        }
        else if (mSelected->canFight(dest))
        {
            mSelected->fight(dest);
            mSoundPlayer.playSound("Fight", 20, 1.2f);

            if (!mSelected->canFight())
            {
                mSelected->select(false);
                mSelected = NULL;
                nextTurn();
            }
        }
        else
        {
            mSelected->select(false);
            mSelected = NULL;
            mSoundPlayer.playSound("Impossible", 10, 1.2f);
        }
    }

    tryToFinish();
}

void Game::nextTurn()
{
    mLightPlayerTurn = !mLightPlayerTurn;

    if (mTurnText.getString() == "Light Player Turn")
        mTurnText.setString("Dark Player Turn");
    else
        mTurnText.setString("Light Player Turn");

    sf::FloatRect rect = mTurnText.getLocalBounds();
    mTurnText.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
}

void Game::tryToFinish()
{
    if (mBoard.pawnCount(true) == 0 || mBoard.pawnCount(false) == 0)
        mFinished = true;
}

void Game::handleEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            handlePlayerAction(sf::Vector2i{ event.mouseButton.x / 64 - 5, event.mouseButton.y / 64 - 1 });
    }
}

void Game::render()
{
    mWindow.clear();
    mBoard.draw(&mWindow);
    mWindow.draw(mTurnText);
    mWindow.display();
}

void Game::run()
{
    while (mWindow.isOpen())
    {
        handleEvents();

        if (mFinished)
            mWindow.close();

        render();
    }
}
