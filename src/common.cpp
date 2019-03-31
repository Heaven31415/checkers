#include "common.hpp"

sf::Vector2i getMousePosOnBoard(sf::RenderWindow& window)
{
    return sf::Mouse::getPosition(window) / 64;
}
