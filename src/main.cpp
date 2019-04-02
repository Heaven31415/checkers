#include <iostream>

#include "board.hpp"
#include "pawn.hpp"

int main()
{
    sf::RenderWindow window{ sf::VideoMode{896, 640}, "Checkers" };

    Resources resources{};
    Board board{&resources};
    Pawn* selected = nullptr;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i dest = { event.mouseButton.x / 64 - 5, event.mouseButton.y / 64 - 1 };

                if (selected)
                {
                    selected->select(false);

                    if (selected->canMove(dest))
                    {
                        selected->move(dest);
                        std::cout << "You moved to new position" << '\n';
                    }
                    else if (selected->canFight(dest))
                    {
                        selected->fight(dest);
                        std::cout << "You killed someone" << '\n';
                    }

                    selected = NULL;
                }
                else
                {
                    selected = board.getPawn(dest);
                    if (selected) selected->select(true);
                }
            }
        }

        window.clear();
        board.draw(&window);
        window.display();
    }
}