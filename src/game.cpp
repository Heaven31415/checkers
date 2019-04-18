#include "game.hpp"
#include "state_stack.hpp"

Game::Game()
: mBoard{}
, mSelected{ nullptr }
, mLock{ false }
, mTraining{ true }
, mPlayerColor{ Color::Light }
, mActualPlayerColor{ Color::Light }
, mSearchDepth{ 4 }
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

    tryToFinish();
}

Pawn* Game::handleEnemyAction()
{
    if (mSelected)
    {
        auto fightPositions = mSelected->getFightPositions();
        if (!fightPositions.empty())
        {
            mSelected->fight(fightPositions[0]);
            SoundPlayer::get().play("Fight", 20, 1.2f);
            return mSelected;
        }
    }

    auto pawns = mBoard.getPawns(mActualPlayerColor);

    std::vector<Pawn*> kings{};

    for (const auto& pawn : pawns)
        if (pawn->isKing()) kings.push_back(pawn);

    pawns.erase(
        std::remove_if(
            pawns.begin(),
            pawns.end(),
            [](Pawn* pawn) { return pawn->isKing(); }
        ),
        pawns.end()
    );

    for (const auto& king : kings)
    {
        auto fightPositions = king->getFightPositions();
        if (fightPositions.empty()) continue;

        king->fight(fightPositions[0]);
        SoundPlayer::get().play("Fight", 20, 1.2f);
        return king;
    }

    for (const auto& pawn : pawns)
    {
        auto fightPositions = pawn->getFightPositions();
        if (fightPositions.empty()) continue;

        pawn->fight(fightPositions[0]);
        SoundPlayer::get().play("Fight", 20, 1.2f);
        return pawn;
    }

    for (const auto& pawn : pawns)
    {
        auto movePositions = pawn->getMovePositions();
        if (movePositions.empty()) continue;

        pawn->move(movePositions[0]);
        SoundPlayer::get().play("Move", 20, 1.2f);
        return nullptr;
    }

    for (const auto& king : kings)
    {
        auto movePositions = king->getMovePositions();
        if (movePositions.empty()) continue;

        king->move(movePositions[0]);
        SoundPlayer::get().play("Move", 20, 1.2f);
        return nullptr;
    }

    return nullptr;
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

void Game::tryToFinish()
{
    if ((!mBoard.isFightPossible(mActualPlayerColor) && !mBoard.isMovePossible(mActualPlayerColor)) || mBoard.pawnCount(mActualPlayerColor) == 0)
    {
        mFinished = true;
        mTurnText.setString(mActualPlayerColor == Color::Light ? "Black Player Won!" : "White Player Won!");
        centerOrigin(mTurnText);
    }
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
            else if (event.key.code == sf::Keyboard::M)
            {
                auto board = mBoard.getAI();
                auto move = ai::getNextMove(board.get(), mActualPlayerColor, mSearchDepth);

                if (move.type == ai::Move::Type::Fight)
                    std::cout << "Fight {";
                else
                    std::cout << "Move {";

                std::cout << move.start.x << "," << move.start.y << "} -> {" << move.end.x << "," << move.end.y << "}\n";
            }
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
    if (!mFinished && !mTraining && mActualPlayerColor != mPlayerColor)
    {
        mEnemyTimer += dt;

        if (mEnemyTimer >= sf::seconds(1.f))
        {
            mSelected = handleEnemyAction();

            if (mSelected && mSelected->canFight())
            {
                mEnemyTimer = sf::seconds(0.5f);
            }
            else
            {
                mSelected = nullptr;
                mEnemyTimer = sf::Time::Zero;
                nextTurn();

                tryToFinish();
            }
        }
    }
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mBoard, states);
    target.draw(mTurnText, states);
}