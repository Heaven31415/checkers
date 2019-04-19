#pragma once

#include "common.hpp"
#include "state.hpp"

class Options : public State
{
public:
    Options();

    virtual void onPush(void* data) override;
    virtual void onPop(void* data) override;
    virtual void onFocusGain() override;
    virtual void onFocusLoss() override;

    virtual void processEvent(const sf::Event& event) override;
    virtual void update(sf::Time dt) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};