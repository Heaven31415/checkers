#include "title.hpp"
#include "state_stack.hpp"

Title::Title()
{
}

void Title::activation()
{
    std::cout << "Title has been activated!" << '\n';
}

void Title::deactivation()
{
    std::cout << "Title has been deactivated!" << '\n';
}

void Title::processEvent(const sf::Event& event)
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
            if (event.key.code == sf::Keyboard::Enter)
                StateStack::get().push(State::Type::Game);
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
