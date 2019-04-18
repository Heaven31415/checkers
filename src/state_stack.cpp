#include "state_stack.hpp"

StateStack::StateStack()
: mWindow{ sf::VideoMode{unsigned(WindowWidth), unsigned(WindowHeight)}, "Checkers", sf::Style::Close }
, mTexture{}
, mStates{}
, mStack{}
, mBackground{ Resources::get().texture("Background") }
, mGlobalTimer{}
, mCursor{ Resources::get().texture("Cursor") }
, mTransition{ false }
, mTransitionTimer{}
{
    if (!mTexture.create(WindowWidth, WindowHeight))
        throw std::runtime_error("Unable to create RenderTexture because create method failed");

    sf::Image icon{};
    if (!icon.loadFromFile(TexturesDirectory + "/" + "Icon.png"))
        throw std::runtime_error("Unable to load Icon because loadFromFile method failed");

    mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    mStates[State::Type::Game] = State::Ptr(new Game{});
    mStates[State::Type::Options] = State::Ptr(new Options{});
    mStates[State::Type::Title] = State::Ptr(new Title{});

    mWindow.setMouseCursorVisible(false);
    mCursor.setOrigin(5.f, 0.f);

    Resources::get().shader("Selection")->setUniform("texture", sf::Shader::CurrentTexture);
    Resources::get().shader("Shadow")->setUniform("texture", sf::Shader::CurrentTexture);
    Resources::get().shader("Transition")->setUniform("texture", sf::Shader::CurrentTexture);
}

void StateStack::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if(!mTransition) mStack.top()->processEvent(event);
    }
}

void StateStack::update(sf::Time dt)
{
    mGlobalTimer += dt;

    Resources::get().shader("Shadow")->setUniform("time", globalTimer().asSeconds());
    mCursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow)));
    mStack.top()->update(dt);

    // SoundPlayer::get().updateMusic();
}

void StateStack::render()
{
    sf::RenderStates states;

    if (mTransition)
    {
        float progress = mTransitionTimer.asSeconds();

        auto* transition = Resources::get().shader("Transition");
        transition->setUniform("progress", mTransitionTimer / sf::seconds(1.0f));
        states.shader = transition;

        mTransitionTimer += TimePerFrame;

        if (mTransitionTimer >= sf::seconds(1.0f)) mTransition = false;
    }

    mTexture.clear(sf::Color::Transparent);
    mTexture.draw(*mStack.top(), states);
    mTexture.display();

    mWindow.clear();

    mWindow.draw(mBackground, Resources::get().shader("Shadow"));

    sf::Sprite sprite{ mTexture.getTexture() };

    mWindow.draw(sprite);
    mWindow.draw(mCursor);

    mWindow.display();
}

void StateStack::transition()
{
    mTransition = true;
    mTransitionTimer = sf::Time::Zero;
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

    transition();
}

void StateStack::pop()
{
    if (mStack.empty())
        throw std::runtime_error("Unable to pop an empty stack");

    mStack.top()->deactivation();
    mStack.pop();

    transition();
}

void StateStack::run()
{
    while (!mStack.empty() && mWindow.isOpen())
    {
        sf::Clock clock{};

        processEvents();
        update(TimePerFrame);
        render();

        sf::sleep(TimePerFrame - clock.restart());
    }
}

void StateStack::closeWindow()
{
    mWindow.close();
}

sf::Time StateStack::globalTimer()
{
    return mGlobalTimer;
}