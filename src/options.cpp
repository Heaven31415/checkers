#include "options.hpp"
#include "state_stack.hpp"

Options::Options()
{
}

void Options::activation()
{
    std::cout << "Options has been activated!" << '\n';
}

void Options::deactivation()
{
    std::cout << "Options has been deactivated!" << '\n';
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

void Options::render(sf::RenderWindow& window) const
{
}
