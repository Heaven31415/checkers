#include "options.hpp"
#include "state_stack.hpp"

Options::Options()
: mBackground{Resources::get().texture("Options")}
{
}

void Options::activation()
{
}

void Options::deactivation()
{
}

void Options::processEvent(const sf::Event& event)
{
    switch (event.type)
    {
        case sf::Event::Closed:
        {
            StateStack::get().closeWindow();
        }
        break;

        case sf::Event::KeyPressed:
        {
            if (event.key.code == sf::Keyboard::Escape)
                StateStack::get().pop();
        }
        break;
    }
}

void Options::update(sf::Time dt)
{
}

void Options::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mBackground, states);
}
