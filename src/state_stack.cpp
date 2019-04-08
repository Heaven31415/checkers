#include "state_stack.hpp"

StateStack::StateStack()
: mWindow{ sf::VideoMode{unsigned(WindowWidth), unsigned(WindowHeight)}, "Checkers", sf::Style::Close }
, mStates{}
, mStack{}
{
    mWindow.setFramerateLimit(60);

    sf::Image icon{};
    if (!icon.loadFromFile("resources/Icon.png"))
        throw std::runtime_error("Unable to load Icon from 'resources/Icon.png' because loadFromFile method failed");

    mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void StateStack::pushImpl(State::Type type)
{
    mStack.push(type);
}

void StateStack::popImpl()
{
    if (!mStack.empty()) mStack.pop();
}

void StateStack::runImpl()
{
    while (!mStack.empty() && mWindow.isOpen())
    {
        auto actual = mStack.top();

        if (mStates.find(actual) == mStates.end())
        {
            mStates[actual] = factory(actual);

            if (mStates[actual] == nullptr)
                throw std::runtime_error("Unable to construct state using factory");
        }
        else
        {
            sf::Event event;
            while (mWindow.pollEvent(event))
                mStates[actual]->processEvent(event);

            mStates[actual]->update();
            mStates[actual]->render(mWindow);
        }
    }
}

StateStack& StateStack::getInstance()
{
    static StateStack instance{};
    return instance;
}

void StateStack::push(State::Type type)
{
    getInstance().pushImpl(type);
}

void StateStack::pop()
{
    getInstance().popImpl();
}

void StateStack::run()
{
    getInstance().runImpl();
}

State::Ptr StateStack::factory(State::Type type)
{
    switch (type)
    {
        case State::Type::Title:
            return nullptr;
        case State::Type::Game:
            return State::Ptr(new Game{});
        case State::Type::Menu:
            return nullptr;
    }

    return nullptr;
}