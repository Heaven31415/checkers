#pragma once

#include <memory>

class State
{
public:
    using Ptr = std::unique_ptr<State>;

    enum class Type
    {
        Title,
        Game,
        Menu,
        Exit
    };

    virtual ~State() {};
    virtual void processEvent(const sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) const = 0;
};