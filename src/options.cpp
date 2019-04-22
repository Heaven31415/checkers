#include "options.hpp"
#include "state_stack.hpp"

Options::Options()
: mHeader{ "Options", Resources::get().font("Candara"), 70 }
, mNextSong{ "Next Song", 224.f, []() {
    SoundPlayer::get().playMusic(false);
    SoundPlayer::get().updateMusic();
    SoundPlayer::get().playMusic(true);
} }
// , mMusicVolume{}
// , mSoundsVolume{}
, mBack{ "Back", 224.f + 384.f, []() {
   StateStack::get().pop();
} }
, mTransition{}
, mTransitionTimer{}
{
    centerOrigin(mHeader);
    mHeader.setPosition(WindowWidth / 2.f, 96.f);
    mHeader.setOutlineThickness(2.f);
}

void Options::onPush(void* data)
{
    mTransition = true;
    mTransitionTimer = sf::Time::Zero;
}

void Options::onPop(void* data)
{

}

void Options::onFocusGain()
{
}

void Options::onFocusLoss()
{

}

void Options::processEvent(const sf::Event& event)
{
    if (mTransition) return;

    switch (event.type)
    {
        case sf::Event::Closed:
        {
            StateStack::get().closeWindow();
        } break;

        case sf::Event::KeyPressed:
        {
            if (event.key.code == sf::Keyboard::Escape) StateStack::get().pop();
        } break;
    }

    mNextSong.processEvent(event);
    mBack.processEvent(event);
}

void Options::update(sf::Time dt)
{
    if (mTransition)
    {
        mTransitionTimer += TimePerFrame;
        if (mTransitionTimer >= sf::seconds(1.0f)) mTransition = false;
    }

    mNextSong.update(dt);
    mBack.update(dt);
}

void Options::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mTransition) states.shader = Shaders::transition(mTransitionTimer / sf::seconds(1.0f));

    target.draw(mNextSong, states);
    target.draw(mBack, states);

    if (!mTransition) states.shader = Shaders::wave(StateStack::get().globalTimer().asSeconds(), { 1.f, 1.f });

    target.draw(mHeader, states);
}