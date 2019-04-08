#pragma once

#include "state.hpp"

class Title : public State
{
public:
    Title();

    virtual void processEvent(const sf::Event& event) override;
    virtual void update() override;
    virtual void render(sf::RenderWindow& window) const override;
};