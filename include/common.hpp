#pragma once

#include <SFML/Graphics.hpp>

const sf::Color LightColor = sf::Color{ 180, 180, 180 };
const sf::Color DarkColor = sf::Color{ 20, 20, 20 };

const int LightPlayerID = 0;
const int DarkPlayerID = 1;

sf::Vector2i getMousePosOnBoard(sf::RenderWindow& window);
