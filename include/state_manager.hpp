#pragma once

#include <map>
#include "game.hpp"
#include "state.hpp"

class StateManager
{
public:
    StateManager();
    StateManager(const StateManager&) = delete;
    StateManager& operator=(const StateManager&) = delete;

    void run();
private:
    State::Ptr factory(State::Type type);

    std::map<State::Type, State::Ptr> mStates;
    State::Type mNext;
};