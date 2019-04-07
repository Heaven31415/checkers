#include "state_manager.hpp"

StateManager::StateManager()
: mStates{}
, mNext{State::Type::Game}
{
}

void StateManager::run()
{
    while (mNext != State::Type::Exit)
    {
        if (mStates[mNext] == nullptr)
            mStates[mNext] = factory(mNext);
        else
            mNext = mStates[mNext]->run();
    }
}

State::Ptr StateManager::factory(State::Type type)
{
    switch (type)
    {
        case State::Type::Title:
            return nullptr;
        case State::Type::Game:
            return State::Ptr(new Game{});
        case State::Type::Menu:
            return nullptr;
        case State::Type::Exit:
            return nullptr;
    }

    return nullptr;
}