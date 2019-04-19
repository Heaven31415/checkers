#pragma once

#include "common.hpp"
#include "state.hpp"

class Options : public State
{
public:
    Options();

    virtual void activation(const std::vector<Message>& messages) override;
    virtual void deactivation() override;
    virtual void processEvent(const sf::Event& event) override;
    virtual void update(sf::Time dt) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite mBackground;
};