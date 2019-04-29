#include "slider.hpp"

Slider::Slider(int min, int max, int current, float height, std::function<void(int)> callback)
: mMin{ min }
, mIntervalLength{ SliderWidth / static_cast<float>(max - min) }
, mBar{ Resources::get().texture("Bar") }
, mArrow{ Resources::get().texture("Arrow") }
, mMoving{}
, mCallback{ callback }
{
    centerOrigin(mBar);
    mBar.setPosition(WindowWidth / 2.f, height);

    centerOrigin(mArrow);
    mArrow.setPosition(WindowWidth / 2.f, height);

    moveArrow(static_cast<float>(current - min) * mIntervalLength);
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

                if (abs(x - mBar.getPosition().x) <= SliderWidth / 2.f && abs(y - mBar.getPosition().y) <= SliderHeight / 2.f)
                {
                    moveArrow(x - (mBar.getPosition().x - SliderWidth / 2.f));
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

                auto dx = x - (mBar.getPosition().x - SliderWidth / 2.f);

                if (x - mBar.getPosition().x >= SliderWidth / 2.f) dx = SliderWidth;
                else if (x - mBar.getPosition().x <= -SliderWidth / 2.f) dx = 0.f;

                moveArrow(dx);
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

void Slider::moveArrow(float dx)
{
    int intervalCount = static_cast<int>(dx / mIntervalLength);
    int value = mMin + intervalCount;

    mArrow.setPosition(mBar.getPosition().x - SliderWidth / 2.f + mIntervalLength * static_cast<float>(intervalCount), mArrow.getPosition().y);
    mCallback(value);
}
