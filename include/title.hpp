#pragma once

#include "state.hpp"

class Title : public State
{
public:
    Title();

    virtual void activation() override;
    virtual void deactivation() override;
    virtual void processEvent(const sf::Event& event) override;
    virtual void update(sf::Time dt) override;
    virtual void render(sf::RenderWindow& window) const override;
};