#include "common.hpp"

bool validatePosition(int x, int y)
{
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

bool validatePosition(sf::Vector2i position)
{
    return position.x >= 0 && position.x < 8 && position.y >= 0 && position.y < 8;
}