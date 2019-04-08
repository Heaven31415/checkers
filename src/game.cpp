#include "game.hpp"
#include "state_stack.hpp"

Game::Game()
: mBoard{}
, mSelected{nullptr}
, mLock{false}
, mActualPlayerColor{Color::Light}
, mTurnText{"White Player Turn", Resources::getFont("Candara"), 30}
, mFinished{false}
{
    centerOrigin(mTurnText);
    mTurnText.setPosition(WindowWidth / 2.f, 96.f);
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
            mTurnText.setString("Black Player Won!");
        else
            mTurnText.setString("White Player Won!");

        centerOrigin(mTurnText);
    }
}

void Game::nextTurn()
{
    if (mActualPlayerColor == Color::Light)
    {
        mActualPlayerColor = Color::Dark;
        mTurnText.setString("Black Player Turn");
    }
    else
    {
        mActualPlayerColor = Color::Light;
        mTurnText.setString("White Player Turn");
    }
   
    centerOrigin(mTurnText);
}

void Game::processEvent(const sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::Closed:
        {
            StateStack::closeWindow();
        }
        break;

        case sf::Event::KeyPressed:
        {
            if (mFinished)
                StateStack::pop();
            else if (event.key.code == sf::Keyboard::F4 && event.key.alt)
                StateStack::pop();
            else if (event.key.code == sf::Keyboard::Escape)
                StateStack::push(State::Type::Menu);
        } 
        break;

        case sf::Event::MouseButtonPressed:
        {
            if (mFinished)
                StateStack::pop();
            else if (!mFinished && event.mouseButton.button == sf::Mouse::Left)
                handlePlayerAction({ event.mouseButton.x / TileSize - OffsetX, event.mouseButton.y / TileSize - OffsetY });
        } 
        break;
    }
}

void Game::update()
{
}

void Game::render(sf::RenderWindow& window) const
{
    window.draw(mBoard);
    window.draw(mTurnText);
}