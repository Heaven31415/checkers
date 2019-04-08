#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

const int BoardWidth = 8;
const int BoardHeight = 8;
const int WindowWidth = 640;
const int WindowHeight = 768;
const int TileSize = 64;
const int OffsetX = 1;
const int OffsetY = 3;

enum class Color
{
    Light,
    Dark
};

bool isValidPosition(int x, int y);
bool isValidPosition(const sf::Vector2i& position);