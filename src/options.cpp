#include "options.hpp"
#include "state_stack.hpp"

Options::Options()
{
}

void Options::processEvent(const sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::Closed:
        {
            StateStack::closeWindow();
        }
        break;

        case sf::Event::KeyPressed:
        {
            if (event.key.code == sf::Keyboard::Escape)
                StateStack::pop();
        }
        break;
    }
}

void Options::update(sf::Time dt)
{
}

void Options::render(sf::RenderWindow& window) const
{
}
