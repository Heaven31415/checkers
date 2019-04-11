#include "game.hpp"
#include "state_stack.hpp"

Game::Game()
: mBoard{}
, mSelected{ nullptr }
, mLock{ false }
, mTraining{ false }
, mPlayerColor{ Color::Light }
, mActualPlayerColor{ Color::Light }
, mEnemyTimer{}
, mTurnText{ "White Player Turn", Resources::get().font("Candara"), 30 }
, mFinished{ false }
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
            SoundPlayer::get().play("Impossible", 10, 1.2f);
        }
    }
    else
    {
        bool canFight = mSelected->canFight();

        if (canFight && mSelected->canFight(destination))
        {
            mSelected->fight(destination);
            SoundPlayer::get().play("Fight", 20, 1.2f);

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
            SoundPlayer::get().play("Move", 20, 1.2f);
        }
        else if(!mLock)
        {
            mSelected->select(false);
            mSelected = nullptr;
            SoundPlayer::get().play("Impossible", 10, 1.2f);
        }
        else
        {
            SoundPlayer::get().play("Impossible", 10, 1.2f);
        }
    }

    if ((!mBoard.isFightPossible(mActualPlayerColor) && !mBoard.isMovePossible(mActualPlayerColor)) || mBoard.pawnCount(mActualPlayerColor) == 0)
    {
        mFinished = true;
        mTurnText.setString(mActualPlayerColor == Color::Light ? "Black Player Won!" : "White Player Won!");
        centerOrigin(mTurnText);
    }
}

void Game::handleEnemyAction()
{
    nextTurn();
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

void Game::activation()
{
}

void Game::deactivation()
{
    mBoard.reset();
    mSelected = nullptr;
    mLock = false;
    mActualPlayerColor = Color::Light;
    mFinished = false;

    mTurnText.setString("White Player Turn");
    centerOrigin(mTurnText);
}

void Game::processEvent(const sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::Closed:
        {
            StateStack::get().closeWindow();
        }
        break;

        case sf::Event::KeyPressed:
        {
            if (mFinished || (event.key.code == sf::Keyboard::F4 && event.key.alt))
                StateStack::get().pop();
            else if (event.key.code == sf::Keyboard::Escape)
                StateStack::get().push(State::Type::Options);
        } 
        break;

        case sf::Event::MouseButtonPressed:
        {
            if (mFinished)
                StateStack::get().pop();
            else if (!mFinished && event.mouseButton.button == sf::Mouse::Left)
            {
                if(mTraining || (!mTraining && mActualPlayerColor == mPlayerColor))
                    handlePlayerAction({ event.mouseButton.x / TileSize - OffsetX, event.mouseButton.y / TileSize - OffsetY });
            }
        } 
        break;
    }
}

void Game::update(sf::Time dt)
{
    if (!mTraining && mActualPlayerColor != mPlayerColor)
    {
        mEnemyTimer += dt;

        if (mEnemyTimer >= sf::seconds(1.f))
        {
            handleEnemyAction();
            mEnemyTimer = sf::Time::Zero;
        }
    }
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mBoard, states);
    target.draw(mTurnText, states);
}