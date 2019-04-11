#pragma once

#include <map>
#include <stack>
#include "game.hpp"
#include "options.hpp"
#include "state.hpp"
#include "title.hpp"

#include <iostream>

class StateStack
{
public:
    StateStack(const StateStack&) = delete;
    StateStack& operator=(const StateStack&) = delete;

    static StateStack& get();

    void push(State::Type type);
    void pop();
    void run();
    void closeWindow();
private:
    StateStack();

    void processEvents();
    void update(sf::Time dt);
    void render();

    sf::RenderWindow mWindow;
    std::map<State::Type, State::Ptr> mStates;
    std::stack<State*> mStack;
    sf::Sprite mBackground;
    sf::Sprite mShadow[2];
    sf::Sprite mCursor;

    bool mTransition;
    sf::Time mTransitionTimer;
};