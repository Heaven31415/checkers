#include "board.hpp"
#include "pawn.hpp"

#include <iostream>

int main()
{
    sf::RenderWindow window{ sf::VideoMode{512, 512, 32}, "Checkers" };

    Board board{};
    Pawn* selected = nullptr;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
            {
                sf::Vector2i dest = getMousePosOnBoard(window);

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
        board.draw(window);
        window.display();
    }
}