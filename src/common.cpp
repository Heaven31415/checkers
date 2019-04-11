#include "common.hpp"

bool isValidPosition(int x, int y)
{
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

bool isValidPosition(const sf::Vector2i& position)
{
    return position.x >= 0 && position.x < 8 && position.y >= 0 && position.y < 8;
}

void centerOrigin(sf::Text& text)
{
    sf::FloatRect rect = text.getLocalBounds();
    text.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
}

size_t randomInt(size_t min, size_t max)
{
    std::uniform_int_distribution<size_t> dist(min, max);
    return dist(engine);
}