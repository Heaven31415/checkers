#include "button.hpp"

Button::Button(const std::string& text, float height, std::function<void()> callback)
: mSprite{ Resources::get().texture("Button") }
, mText{ text, Resources::get().font("Candara"), 30 }
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
                mHover = true;
            else
            {
                mHover = false;
                mTimer = sf::Time::Zero;
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
                    mTimer = sf::Time::Zero;
                }
            }
        } break;
    }
}

void Button::update(sf::Time dt)
{
    if (mHover) mTimer += dt;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mHover) states.shader = Shaders::selection(mTimer.asSeconds());

    target.draw(mSprite, states);
    target.draw(mText, states);
}