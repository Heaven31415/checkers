#include "title.hpp"
#include "state_stack.hpp"

Title::Title()
{
}

void Title::processEvent(const sf::Event& event)
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
            if (event.key.code == sf::Keyboard::Enter)
                StateStack::push(State::Type::Game);
        }
        break;
    }
}

void Title::update(sf::Time dt)
{
}

void Title::render(sf::RenderWindow& window) const
{

}
