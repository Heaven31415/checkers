#pragma once

#include <map>
#include <stack>
#include "game.hpp"
#include "state.hpp"

class StateStack
{
public:
    StateStack(const StateStack&) = delete;
    StateStack& operator=(const StateStack&) = delete;

    static StateStack& getInstance();
    static void push(State::Type type);
    static void pop();
    static void run();
private:
    StateStack();

    void pushImpl(State::Type type);
    void popImpl();
    void runImpl();

    State::Ptr factory(State::Type type);

    sf::RenderWindow mWindow;
    std::map<State::Type, State::Ptr> mStates;
    std::stack<State::Type> mStack;
};