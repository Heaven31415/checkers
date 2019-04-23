#include "slider.hpp"

Slider::Slider(float value, float height, std::function<void(float)> callback)
: mBar{ Resources::get().texture("Bar") }
, mArrow{ Resources::get().texture("Arrow") }
, mMoving{}
, mCallback{ callback }
{
    centerOrigin(mBar);
    mBar.setPosition(WindowWidth / 2.f, height);

    centerOrigin(mArrow);
    mArrow.setPosition(WindowWidth / 2.f, height);

    moveArrow(mBar.getPosition().x - 192.f + value / 100.f * 192.f * 2.f);
}

void Slider::processEvent(const sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                auto x = float(event.mouseButton.x);
                auto y = float(event.mouseButton.y);

                if (abs(x - mBar.getPosition().x) <= 192.f && abs(y - mBar.getPosition().y) <= 24.f)
                {
                    moveArrow(x);
                    mMoving = true;
                }
            }
        } break;

        case sf::Event::MouseButtonReleased:
        {
            mMoving = false;
        } break;

        case sf::Event::MouseMoved:
        {
            if (mMoving)
            {
                auto x = float(event.mouseMove.x);
                auto y = float(event.mouseMove.y);

                if (x - mBar.getPosition().x >= 192.f) x = mBar.getPosition().x + 192.f;
                else if (x - mBar.getPosition().x <= -192.f) x = mBar.getPosition().x - 192.f;

                moveArrow(x);
            }
        } break;
    }
}

void Slider::update(sf::Time dt)
{
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mBar, states);
    target.draw(mArrow, states);
}

void Slider::moveArrow(float x)
{
    mArrow.setPosition(x, mArrow.getPosition().y);

    float value = 50.f * (1 + (x - mBar.getPosition().x) / 192.f);
    mCallback(value);
}
