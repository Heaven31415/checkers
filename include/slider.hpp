#pragma once

#include <functional>
#include "common.hpp"
#include "resources.hpp"
#include "sound_player.hpp"

class Slider : public sf::Drawable
{
public:
    Slider(int min, int max, int current, float height, std::function<void(int)> callback);
    void processEvent(const sf::Event& event);
    void update(sf::Time dt);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void moveArrow(float dx);

private:
    const int mMin;
    const float mIntervalLength;
    sf::Sprite mBar;
    sf::Sprite mArrow;
    bool mMoving;
    std::function<void(int)> mCallback;
};