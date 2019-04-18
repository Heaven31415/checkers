#pragma once

#include <functional>
#include "common.hpp"
#include "state.hpp"

#include <iostream>

class Title : public State
{
public:
    enum class Type
    {
        ChooseOption,
        ChooseMode,
        ChooseDifficulty
    };

    struct Button : public sf::Drawable
    {
        Button(float height, const std::string& string, std::function<void()> callback);
        void processEvent(const sf::Event& event);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Sprite sprite;
        sf::Text text;
        bool hover;
        std::function<void()> callback;
    };

    Title();
    void transition(Type type);

    virtual void activation() override;
    virtual void deactivation() override;
    virtual void processEvent(const sf::Event& event) override;
    virtual void update(sf::Time dt) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Type mType;
    sf::Sprite mFrame;
    sf::Text mHeader;
    std::vector<Button> mChooseOption;
    std::vector<Button> mChooseMode;
    std::vector<Button> mChooseDifficulty;
    bool mTransition;
    sf::Time mTransitionTimer;
};