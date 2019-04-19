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
    mHeader.setPosition(WindowWidth / 2.f, 96.f);
    mHeader.setOutlineThickness(2.f);
    centerOrigin(mHeader);

    // ChooseOption
    mChooseOption.push_back(Button{ 224.f, "New Game", [this]() {
        transition(Type::ChooseMode);
    } });

    mChooseOption.push_back(Button{ 224.f + 128.f, "Options", [this]() {
       transition(Type::ChooseOption);
       StateStack::get().push(State::Type::Options);
    } });

    mChooseOption.push_back(Button{ 224.f + 256.f, "Exit", [this]() {
       StateStack::get().closeWindow();
    } });

    // ChooseMode
    mChooseMode.push_back(Button{ 224.f, "Training", [this]() {
      StateStack::get().push(State::Type::Game, {{Message::Type::Bool, true}});
   } });

    mChooseMode.push_back(Button{ 224.f + 128.f, "Player vs AI", [this]() {
       transition(Type::ChooseDifficulty);
    } });

    mChooseMode.push_back(Button{ 224.f + 256.f, "Back", [this]() {
        transition(Type::ChooseOption);
    } });

    // ChooseDifficulty
    mChooseDifficulty.push_back(Button{ 224.f, "Easy", [this]() {
        transition(Type::ChooseOption);
        StateStack::get().push(State::Type::Game, {{Message::Type::Bool, false}, {Message::Type::Int, 2}});
     } });

    mChooseDifficulty.push_back(Button{ 224.f + 128.f, "Normal", [this]() {
        transition(Type::ChooseOption);
        StateStack::get().push(State::Type::Game, {{Message::Type::Bool, false}, {Message::Type::Int, 4}});
     } });

    mChooseDifficulty.push_back(Button{ 224.f + 256.f, "Hard", [this]() {
        transition(Type::ChooseOption);
        StateStack::get().push(State::Type::Game, {{Message::Type::Bool, false}, {Message::Type::Int, 6}});
    } });

    mChooseDifficulty.push_back(Button{ 224.f + 384.f, "Back", [this]() {
        transition(Type::ChooseMode);
    } });
}

void Title::transition(Type type)
{
    mType = type;

    switch (mType)
    {
        case Type::ChooseOption:
        {
            mHeader.setString("Checkers");
        }
        break;

        case Type::ChooseMode:
        {
            mHeader.setString("Game Mode");
        }
        break;

        case Type::ChooseDifficulty:
        {
            mHeader.setString("Difficulty");
        }
        break;
    }

    centerOrigin(mHeader);

    mTransition = true;
    mTransitionTimer = sf::Time::Zero;
}

void Title::activation(const std::vector<Message>& messages)
{
    transition(Type::ChooseOption);
}

void Title::deactivation()
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
        }
        break;

        case sf::Event::KeyPressed:
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                switch (mType)
                {
                    case Type::ChooseOption:
                    {
                        StateStack::get().closeWindow();
                    }
                    break;

                    case Type::ChooseMode:
                    {
                        transition(Type::ChooseOption);
                    }
                    break;

                    case Type::ChooseDifficulty:
                    {
                        transition(Type::ChooseMode);
                    }
                    break;
                }
            }
        }
        break;
    }

    switch (mType)
    {
        case Type::ChooseOption:
        {
            for (auto& button : mChooseOption) button.processEvent(event);
        }
        break;

        case Type::ChooseMode:
        {
            for (auto& button : mChooseMode) button.processEvent(event);
        }
        break;

        case Type::ChooseDifficulty:
        {
            for (auto& button : mChooseDifficulty) button.processEvent(event);
        }
        break;
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
        }
        break;

        case Type::ChooseMode:
        {
            for (auto& button : mChooseMode) button.update(dt);
        }
        break;

        case Type::ChooseDifficulty:
        {
            for (auto& button : mChooseDifficulty) button.update(dt);
        }
        break;
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
        }
        break;

        case Type::ChooseMode:
        {
            for (const auto& button : mChooseMode) target.draw(button, states);
        }
        break;

        case Type::ChooseDifficulty:
        {
            for (const auto& button : mChooseDifficulty) target.draw(button, states);
        }
        break;
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

Title::Button::Button(float height, const std::string& string, std::function<void()> callback)
: sprite{ Resources::get().texture("Button") }
, text{ string, Resources::get().font("Candara"), 30 }
, hover{ false }
, callback{ callback }
{
    centerOrigin(sprite);
    sprite.setPosition(WindowWidth / 2.f, height);

    centerOrigin(text);
    text.setPosition(WindowWidth / 2.f, height);
    text.setOutlineThickness(1.f);
}

void Title::Button::processEvent(const sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::MouseMoved:
        {
            auto x = float(event.mouseMove.x);
            auto y = float(event.mouseMove.y);

            if (abs(sprite.getPosition().x - x) <= 128.f && abs(sprite.getPosition().y - y) <= 32.f) 
                hover = true;
            else
            {
                hover = false;
                timer = sf::Time::Zero;
            }
                
        }
        break;

        case sf::Event::MouseButtonReleased:
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                auto x = float(event.mouseButton.x);
                auto y = float(event.mouseButton.y);

                if (abs(sprite.getPosition().x - x) <= 128.f && abs(sprite.getPosition().y - y) <= 32.f)
                {
                    callback();
                    hover = false;
                    timer = sf::Time::Zero;
                }
            }
        }
        break;
    }
}

void Title::Button::update(sf::Time dt)
{
    if (hover) timer += dt;
}

void Title::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (hover)
    {
        sf::Shader* shader = Resources::get().shader("Selection");
        shader->setUniform("time", timer.asSeconds());
        states.shader = shader;
    }

    target.draw(sprite, states);
    target.draw(text, states);
}
