#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

enum class Color
{
    Light,
    Dark
};

bool isValidPosition(int x, int y);
bool isValidPosition(const sf::Vector2i& position);