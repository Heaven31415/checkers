#include "state_stack.hpp"

StateStack::StateStack()
: mWindow{ sf::VideoMode{unsigned(WindowWidth), unsigned(WindowHeight)}, "Checkers", sf::Style::Close }
, mActual{ State::Type::None }
, mStates{}
, mStack{}
, mCursor{Resources::get().texture("Cursor")}
{
    sf::Image icon{};
    if (!icon.loadFromFile("resources/Icon.png"))
        throw std::runtime_error("Unable to load Icon from 'resources/Icon.png' because loadFromFile method failed");

    mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    mStates[State::Type::Game] = State::Ptr(new Game{});
    mStates[State::Type::Options] = State::Ptr(new Options{});
    mStates[State::Type::Title] = State::Ptr(new Title{});

    mWindow.setMouseCursorVisible(false);
    mCursor.setOrigin(5.f, 0.f);
}

StateStack& StateStack::get()
{
    static StateStack instance{};
    return instance;
}

void StateStack::push(State::Type type)
{
    mStack.push(type);
}

void StateStack::pop()
{
    if (!mStack.empty()) mStack.pop();
}

void StateStack::run()
{
    while (!mStack.empty() && mWindow.isOpen())
    {
        if (mActual != mStack.top())
        {
            mActual = mStack.top();
            mStates[mActual]->activation();
        }

        sf::Clock clock{};

        sf::Event event;
        while (mWindow.pollEvent(event))
            mStates[mActual]->processEvent(event);

        mStates[mActual]->update(TimePerFrame);
        updateCursor();

        mWindow.clear();
        mStates[mActual]->render(mWindow);
        mWindow.draw(mCursor);
        mWindow.display();

        sf::sleep(TimePerFrame - clock.restart());
    }
}

void StateStack::closeWindow()
{
    mWindow.close();
}

void StateStack::updateCursor()
{
    mCursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow)));
}