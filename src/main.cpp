#include <iostream>

#include "board.hpp"
#include "pawn.hpp"

void nextTurn(bool* lightPlayerTurn, sf::Text* turnText)
{
    *lightPlayerTurn = !(*lightPlayerTurn);

    if (turnText->getString() == "Light Player Turn")
        turnText->setString("Dark Player Turn");
    else
        turnText->setString("Light Player Turn");
}

int main()
{
    sf::RenderWindow window{ sf::VideoMode{896, 640}, "Checkers" };
    Resources resources{};
    Board board{&resources};
    Pawn* selected = nullptr;
    bool lightPlayerTurn = true;

    sf::Text turnText{ "Light Player Turn", resources.getFont(), 30 };

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
                bool fightPossible = board.isFightPossible(lightPlayerTurn);

                if (!selected)
                {
                    selected = board.getPawn(dest);
                    if (selected && selected->isLight() == lightPlayerTurn && (!fightPossible || (fightPossible && selected->canFight())))
                        selected->select(true);
                    else
                        selected = NULL;
                }
                else
                {
                    if (selected->canMove(dest))
                    {
                        selected->select(false);
                        selected->move(dest);
                        selected = NULL;
                        nextTurn(&lightPlayerTurn, &turnText);
                        std::cout << "You moved a pawn to a new position" << '\n';
                    }
                    else if (selected->canFight(dest))
                    {
                        selected->fight(dest);

                        if (selected->canFight())
                        {
                            std::cout << "You killed someone and you can kill again" << '\n';
                        }
                        else
                        {
                            selected->select(false);
                            selected = NULL;
                            nextTurn(&lightPlayerTurn, &turnText);
                            std::cout << "You killed someone" << '\n';
                        }
                    }
                    else
                    {
                        selected->select(false);
                        selected = NULL;
                    }
                }
            }
        }

        window.clear();
        board.draw(&window);
        window.draw(turnText);
        window.display();
    }
}