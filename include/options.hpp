#pragma once

#include "button.hpp"
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

private:
    sf::Text mHeader;
    Button mNextSong;
    // Slider mMusicVolume;
    // Slider mSoundsVolume;
    Button mBack;

    bool mTransition;
    sf::Time mTransitionTimer;
};