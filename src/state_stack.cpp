#include "state_stack.hpp"

StateStack::StateStack()
: mWindow{ sf::VideoMode{unsigned(WindowWidth), unsigned(WindowHeight)}, "Checkers", sf::Style::Close }
, mStates{}
, mStack{}
, mCursor{ Resources::get().texture("Cursor") }
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
    mStack.push(mStates[type].get());
    mStack.top()->activation();
}

void StateStack::pop()
{
    if (mStack.empty())
        throw std::runtime_error("Unable to pop an empty stack");

    mStack.top()->deactivation();
    mStack.pop();
}

void StateStack::run()
{
    while (!mStack.empty() && mWindow.isOpen())
    {
        auto* state = mStack.top();

        sf::Clock clock{};

        sf::Event event;
        while (mWindow.pollEvent(event))
            state->processEvent(event);

        state->update(TimePerFrame);
        updateCursor();

        mWindow.clear();
        state->render(mWindow);
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