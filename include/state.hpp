#pragma once

#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class State : public sf::Drawable
{
public:
    using Ptr = std::unique_ptr<State>;

    enum class Type
    {
        Game,
        Options,
        Title
    };

    virtual ~State() {};
    virtual void activation() = 0;
    virtual void deactivation() = 0;
    virtual void processEvent(const sf::Event& event) = 0;
    virtual void update(sf::Time dt) = 0;
};