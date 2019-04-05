#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

enum class Color
{
    Light,
    Dark
};

bool validatePosition(int x, int y);
bool validatePosition(const sf::Vector2i& position);