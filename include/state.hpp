#pragma once

#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

class State
{
public:
    using Ptr = std::unique_ptr<State>;

    enum class Type
    {
        None,
        Game,
        Options,
        Title
    };

    virtual ~State() {};
    virtual void activation() = 0;
    virtual void processEvent(const sf::Event& event) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void render(sf::RenderWindow& window) const = 0;
};