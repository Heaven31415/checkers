#include "button.hpp"

Button::Button(const std::string& text, float height, std::function<void()> callback)
: mSprite{ Resources::get().texture("Button") }
, mText{ text, Resources::get().font("Candara"), 30 }
, mSelectionTimer{}
, mSoundTimer{}
, mHover{ false }
, mCallback{ callback }
{
    centerOrigin(mSprite);
    mSprite.setPosition(WindowWidth / 2.f, height);

    centerOrigin(mText);
    mText.setPosition(WindowWidth / 2.f, height);
    mText.setOutlineThickness(1.f);
}

void Button::processEvent(const sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::MouseMoved:
        {
            auto x = float(event.mouseMove.x);
            auto y = float(event.mouseMove.y);

            if (abs(mSprite.getPosition().x - x) <= 128.f && abs(mSprite.getPosition().y - y) <= 32.f)
            {
                mHover = true;
                if (mSoundTimer == sf::Time::Zero) 
                {
                    SoundPlayer::get().play("Hover", 25, 1.0f);
                    mSoundTimer = Resources::get().soundBuffer("Hover").getDuration();
                }
            }
            else
            {
                mHover = false;
                mSelectionTimer = sf::Time::Zero;
            }
        } break;

        case sf::Event::MouseButtonReleased:
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                auto x = float(event.mouseButton.x);
                auto y = float(event.mouseButton.y);

                if (abs(mSprite.getPosition().x - x) <= 128.f && abs(mSprite.getPosition().y - y) <= 32.f)
                {
                    mCallback();
                    mHover = false;
                    mSelectionTimer = sf::Time::Zero;
                    SoundPlayer::get().play("Click", 100, 1.0f);
                }
            }
        } break;
    }
}

void Button::update(sf::Time dt)
{
    if (mHover) mSelectionTimer += dt;

    mSoundTimer -= dt;
    if (mSoundTimer < sf::Time::Zero) mSoundTimer = sf::Time::Zero;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mHover) states.shader = Shaders::selection(mSelectionTimer.asSeconds());

    target.draw(mSprite, states);
    target.draw(mText, states);
}