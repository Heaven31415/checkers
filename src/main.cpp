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
                if (selected)
                {
                    selected->select(false);
                    if (selected->canMove(getMousePosOnBoard(window)))
                    {
                        selected->move(getMousePosOnBoard(window));
                        std::cout << "You moved to new position" << '\n';
                    }

                    sf::Vector2i newPawnPos = getMousePosOnBoard(window);
                    sf::Vector2i killedPawnPos = selected->canFight(newPawnPos);

                    if (killedPawnPos != sf::Vector2i{ 0, 0 })
                    {
                        std::cout << "You can kill it" << '\n';
                        selected->move(newPawnPos);
                        board.killPawn(killedPawnPos);
                    }

                    selected = nullptr;
                }
                else
                {
                    selected = board.getPawn(getMousePosOnBoard(window));
                    if (selected) selected->select(true);
                }
            }
        }

        window.clear();
        board.draw(window);
        window.display();
    }
}