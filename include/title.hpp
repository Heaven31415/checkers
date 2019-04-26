#pragma once

#include "button.hpp"
#include "shaders.hpp"
#include "state.hpp"

class Title : public State
{
public:
    enum class Type
    {
        ChooseOption,
        ChooseMode,
        ChooseDifficulty
    };

    Title();
    void transition(Type type);

    virtual void onPush(State::Message message) override;
    virtual void onPop(State::Message message) override;
    virtual void onFocusGain() override;
    virtual void onFocusLoss() override;

    virtual void processEvent(const sf::Event& event) override;
    virtual void update(sf::Time dt) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    Type mType;
    sf::Text mHeader;
    std::vector<Button> mChooseOption;
    std::vector<Button> mChooseMode;
    std::vector<Button> mChooseDifficulty;
    sf::Text mVersion;
    bool mTransition;
    sf::Time mTransitionTimer;
};