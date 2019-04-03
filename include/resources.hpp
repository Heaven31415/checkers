#pragma once

#include <SFML/Graphics.hpp>

class Resources
{
public:
    Resources();
    sf::Texture& getTexture(std::string name);
    sf::Font& getFont();

private:
    void loadTexture(std::string key, std::string filename);

    std::map<std::string, sf::Texture> mTextures;
    sf::Font mFont;
};