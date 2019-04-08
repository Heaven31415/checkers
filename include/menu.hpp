#pragma once

#include "state.hpp"

class Menu : public State
{
public:
    Menu();

    virtual void processEvent(const sf::Event& event) override;
    virtual void update() override;
    virtual void render(sf::RenderWindow& window) const override;
};