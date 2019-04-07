#include "game.hpp"

Game::Game()
: mWindow{sf::VideoMode{896, 640}, "Checkers", sf::Style::Close}
, mBoard{}
, mSelected{nullptr}
, mLock{false}
, mActualPlayerColor{Color::Light}
, mTurnText{"Light Player Turn", Resources::getFont("Candara"), 30}
, mFinished{false}
{
    mWindow.setFramerateLimit(60);
    
    sf::FloatRect rect = mTurnText.getLocalBounds();
    mTurnText.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
    mTurnText.setPosition(160.f, 64.f);
}

void Game::handlePlayerAction(const sf::Vector2i& destination)
{
    bool fightPossible = mBoard.isFightPossible(mActualPlayerColor);

    if (!mSelected)
    {
        mSelected = mBoard.getPawn(destination);
        if (mSelected && mSelected->getColor() == mActualPlayerColor && (!fightPossible || (fightPossible && mSelected->canFight())))
            mSelected->select(true);
        else
        {
            mSelected = nullptr;
            SoundPlayer::playSound("Impossible", 10, 1.2f);
        }
    }
    else
    {
        bool canFight = mSelected->canFight();

        if (canFight && mSelected->canFight(destination))
        {
            mSelected->fight(destination);
            SoundPlayer::playSound("Fight", 20, 1.2f);

            if (!mSelected->canFight())
            {
                mSelected->select(false);
                mSelected = nullptr;
                nextTurn();
                mLock = false;
            }
            else
            {
                mLock = true;
            }

        }
        else if (!canFight && mSelected->canMove(destination))
        {
            mSelected->move(destination);
            mSelected->select(false);
            mSelected = nullptr;
            nextTurn();
            SoundPlayer::playSound("Move", 20, 1.2f);
        }
        else if(!mLock)
        {
            mSelected->select(false);
            mSelected = nullptr;
            SoundPlayer::playSound("Impossible", 10, 1.2f);
        }
        else
        {
            SoundPlayer::playSound("Impossible", 10, 1.2f);
        }
    }

    if ((!mBoard.isFightPossible(mActualPlayerColor) && !mBoard.isMovePossible(mActualPlayerColor)) || mBoard.pawnCount(mActualPlayerColor) == 0)
    {
        mFinished = true;

        if (mActualPlayerColor == Color::Light)
            mTurnText.setString("Light Player Won!");
        else
            mTurnText.setString("Dark Player Won!");

        sf::FloatRect rect = mTurnText.getLocalBounds();
        mTurnText.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
    }
}

void Game::nextTurn()
{
    if (mActualPlayerColor == Color::Light)
    {
        mActualPlayerColor = Color::Dark;
        mTurnText.setString("Dark Player Turn");
    }
    else
    {
        mActualPlayerColor = Color::Light;
        mTurnText.setString("Light Player Turn");
    }
   
    sf::FloatRect rect = mTurnText.getLocalBounds();
    mTurnText.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
}

void Game::handleEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F4 && event.key.control)
            mWindow.close();
        else if (!mFinished && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            handlePlayerAction(sf::Vector2i { event.mouseButton.x / 64 - 5, event.mouseButton.y / 64 - 1 });
        else if (mFinished && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            mWindow.close();
    }
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mBoard);
    mWindow.draw(mTurnText);
    mWindow.display();
}

void Game::run()
{
    while (mWindow.isOpen())
    {
        handleEvents();
        render();
    }
}