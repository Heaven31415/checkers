#include "menu.hpp"
#include "state_stack.hpp"

Menu::Menu()
{
}

void Menu::processEvent(const sf::Event& event)
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

void Menu::update()
{
}

void Menu::render(sf::RenderWindow& window) const
{
    window.clear(sf::Color::Blue);
    window.display();
}
