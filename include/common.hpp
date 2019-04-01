#pragma once

#include <SFML/Graphics.hpp>

const sf::Color LIGHT_PAWN_COLOR = sf::Color{ 180, 180, 180 };
const sf::Color DARK_PAWN_COLOR = sf::Color{ 20, 20, 20 };

const sf::Color LIGHT_GRID_COLOR = sf::Color{ 136, 167, 216 };
const sf::Color DARK_GRID_COLOR = sf::Color{ 37, 67, 114 };

const int LIGHT_PLAYER_ID = 0;
const int DARK_PLAYER_ID = 1;

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;

const float UNIT_SIZE = 64.f;
const float PAWN_RADIUS = 24.f;

sf::Vector2i getMousePosOnBoard(sf::RenderWindow& window);
