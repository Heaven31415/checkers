#include "resources.hpp"

Resources::Resources()
: mTextures{}
{
    loadTexture("Board", "resources/Board.png");

    loadTexture("LightKing", "resources/LightKing.png");
    loadTexture("LightKingSelected", "resources/LightKingSelected.png");
    loadTexture("LightPawn", "resources/LightPawn.png");
    loadTexture("LightPawnSelected", "resources/LightPawnSelected.png");

    loadTexture("DarkKing", "resources/DarkKing.png");
    loadTexture("DarkKingSelected", "resources/DarkKingSelected.png");
    loadTexture("DarkPawn", "resources/DarkPawn.png");
    loadTexture("DarkPawnSelected", "resources/DarkPawnSelected.png");
}

sf::Texture& Resources::getTexture(std::string name)
{
    return mTextures[name];
}

void Resources::loadTexture(std::string key, std::string filename)
{
    if (mTextures.find(key) == mTextures.end())
    {
        sf::Texture texture;
        if (!texture.loadFromFile(filename))
            throw std::runtime_error("Unable to load '" + filename + "'");

        mTextures[key] = texture;
    }
    else
        throw std::runtime_error("Key '" + key + "' already exists");
    
}
