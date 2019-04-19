#include "state_stack.hpp"
#include "title.hpp"

Title::Title()
: mType{Type::ChooseOption}
, mHeader{"Checkers", Resources::get().font("Candara"), 70}
, mChooseOption{}
, mChooseMode{}
, mChooseDifficulty{}
, mTransition{}
, mTransitionTimer{}
{
    centerOrigin(mHeader);
    mHeader.setPosition(WindowWidth / 2.f, 96.f);
    mHeader.setOutlineThickness(2.f);

    // ChooseOption
    mChooseOption.push_back(Button{ "New Game", 224.f, [this](){
        transition(Type::ChooseMode);
    }});

    mChooseOption.push_back(Button{ "Options", 224.f + 128.f, [this](){
        StateStack::get().push(State::Type::Options);
    }});

    mChooseOption.push_back(Button{ "Exit", 224.f + 256.f, [this](){
        StateStack::get().closeWindow();
    }});

    // ChooseMode
    mChooseMode.push_back(Button{ "Training", 224.f, [this](){
        StateStack::get().push(State::Type::Game, (void*)Message::Training);
    }});

    mChooseMode.push_back(Button{ "Player vs AI", 224.f + 128.f, [this](){
       transition(Type::ChooseDifficulty);
    }});

    mChooseMode.push_back(Button{ "Back", 224.f + 256.f, [this](){
        transition(Type::ChooseOption);
    }});

    // ChooseDifficulty
    mChooseDifficulty.push_back(Button{ "Easy", 224.f, [this]() {
        StateStack::get().push(State::Type::Game, (void*)Message::EasyAI);
     } });

    mChooseDifficulty.push_back(Button{ "Normal", 224.f + 128.f, [this]() {
        StateStack::get().push(State::Type::Game, (void*)Message::NormalAI);
     } });

    mChooseDifficulty.push_back(Button{ "Hard", 224.f + 256.f, [this]() {
        StateStack::get().push(State::Type::Game, (void*)Message::HardAI);
    } });

    mChooseDifficulty.push_back(Button{ "Back", 224.f + 384.f, [this]() {
        transition(Type::ChooseMode);
    } });

    transition(Type::ChooseOption);
}

void Title::transition(Type type)
{
    mType = type;
    mTransition = true;
    mTransitionTimer = sf::Time::Zero;

    switch (mType)
    {
        case Type::ChooseOption:
        {
            mHeader.setString("Checkers");
        } break;

        case Type::ChooseMode:
        {
            mHeader.setString("Game Mode");
        } break;

        case Type::ChooseDifficulty:
        {
            mHeader.setString("Difficulty");
        } break;
    }

    centerOrigin(mHeader);
}

void Title::onPush(void* data)
{

}

void Title::onPop(void* data)
{

}

void Title::onFocusGain()
{
    transition(Type::ChooseOption);
}

void Title::onFocusLoss()
{
}

void Title::processEvent(const sf::Event& event)
{
    if (mTransition) return;

    switch (event.type)
    {
        case sf::Event::Closed:
        {
            StateStack::get().closeWindow();
        } break;

        case sf::Event::KeyPressed:
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                switch (mType)
                {
                    case Type::ChooseOption:
                    {
                        StateStack::get().closeWindow();
                    } break;

                    case Type::ChooseMode:
                    {
                        transition(Type::ChooseOption);
                    } break;

                    case Type::ChooseDifficulty:
                    {
                        transition(Type::ChooseMode);
                    } break;
                }
            }
        } break;
    }

    switch (mType)
    {
        case Type::ChooseOption:
        {
            for (auto& button : mChooseOption) button.processEvent(event);
        } break;

        case Type::ChooseMode:
        {
            for (auto& button : mChooseMode) button.processEvent(event);
        } break;

        case Type::ChooseDifficulty:
        {
            for (auto& button : mChooseDifficulty) button.processEvent(event);
        } break;
    }
}

void Title::update(sf::Time dt)
{
    if (mTransition)
    {
        mTransitionTimer += TimePerFrame;
        if (mTransitionTimer >= sf::seconds(1.0f)) mTransition = false;
    }

    switch (mType)
    {
        case Type::ChooseOption:
        {
            for (auto& button : mChooseOption) button.update(dt);
        } break;

        case Type::ChooseMode:
        {
            for (auto& button : mChooseMode) button.update(dt);
        } break;

        case Type::ChooseDifficulty:
        {
            for (auto& button : mChooseDifficulty) button.update(dt);
        } break;
    }
}

void Title::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mTransition)
    {
        float progress = mTransitionTimer.asSeconds();

        auto* transition = Resources::get().shader("Transition");
        transition->setUniform("progress", mTransitionTimer / sf::seconds(1.0f));
        states.shader = transition;
    }

    switch (mType)
    {
        case Type::ChooseOption:
        {
            for (const auto& button : mChooseOption) target.draw(button, states);
        } break;

        case Type::ChooseMode:
        {
            for (const auto& button : mChooseMode) target.draw(button, states);
        } break;

        case Type::ChooseDifficulty:
        {
            for (const auto& button : mChooseDifficulty) target.draw(button, states);
        } break;
    }

    if (!mTransition)
    {
        auto* wave = Resources::get().shader("Wave");
        wave->setUniform("wave_phase", StateStack::get().globalTimer().asSeconds());
        wave->setUniform("wave_amplitude", sf::Vector2f{ 1.0f, 1.0f });
        states.shader = wave;
    }

    target.draw(mHeader, states);
}