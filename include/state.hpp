#pragma once

#include <memory>

class State
{
public:
    typedef std::unique_ptr<State> Ptr;

    enum class Type
    {
        Title,
        Game,
        Menu,
        Exit
    };

    virtual ~State() {};
    virtual State::Type run() = 0;

protected:
    void nextState(State::Type state)
    {
        mGoToNextState = true;
        mNextState = state;
    }

    bool mGoToNextState{ false };
    State::Type mNextState{ State::Type::Exit };
};

