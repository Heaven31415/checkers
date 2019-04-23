#pragma once

#include <functional>
#include "common.hpp"
#include "resources.hpp"
#include "sound_player.hpp"

class Slider : public sf::Drawable
{
public:
    Slider(float value, float height, std::function<void(float)> callback);
    void processEvent(const sf::Event& event);
    void update(sf::Time dt);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void moveArrow(float x);

private:
    sf::Sprite mBar;
    sf::Sprite mArrow;
    bool mMoving;
    std::function<void(float)> mCallback;
};