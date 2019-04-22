#pragma once

#include <functional>
#include "common.hpp"
#include "resources.hpp"
#include "shaders.hpp"
#include "sound_player.hpp"

class Slider : public sf::Drawable
{
public:
    Slider();
    void processEvent(const sf::Event& event);
    void update(sf::Time dt);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};