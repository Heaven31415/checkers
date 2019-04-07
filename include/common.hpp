#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

const int BoardWidth = 8;
const int BoardHeight = 8;
const int WindowWidth = 896;
const int WindowHeight = 640;
const int TileSize = 64;
const int OffsetX = 5;
const int OffsetY = 1;

enum class Color
{
    Light,
    Dark
};

bool isValidPosition(int x, int y);
bool isValidPosition(const sf::Vector2i& position);