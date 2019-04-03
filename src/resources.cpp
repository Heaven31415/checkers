#include "resources.hpp"

Resources::Resources()
: mSoundBuffers{}
, mTextures{}
, mFont{}
{
    loadSoundBuffer("Fight", "resources/Fight.wav");
    loadSoundBuffer("Impossible", "resources/Impossible.wav");
    loadSoundBuffer("Move", "resources/Move.wav");
    loadSoundBuffer("Win", "resources/Win.wav");

    loadTexture("Board", "resources/Board.png");
    loadTexture("LightKing", "resources/LightKing.png");
    loadTexture("LightKingSelected", "resources/LightKingSelected.png");
    loadTexture("LightPawn", "resources/LightPawn.png");
    loadTexture("LightPawnSelected", "resources/LightPawnSelected.png");
    loadTexture("DarkKing", "resources/DarkKing.png");
    loadTexture("DarkKingSelected", "resources/DarkKingSelected.png");
    loadTexture("DarkPawn", "resources/DarkPawn.png");
    loadTexture("DarkPawnSelected", "resources/DarkPawnSelected.png");

    if(!mFont.loadFromFile("resources/Candara.ttf"))
        throw std::runtime_error("Unable to load 'resources/Candara.ttf'");
}

sf::SoundBuffer& Resources::getSoundBuffer(std::string name)
{
    return mSoundBuffers[name];
}

sf::Texture& Resources::getTexture(std::string name)
{
    return mTextures[name];
}

sf::Font& Resources::getFont()
{
    return mFont;
}

void Resources::loadSoundBuffer(std::string key, std::string filename)
{
    if (mSoundBuffers.find(key) == mSoundBuffers.end())
    {
        sf::SoundBuffer soundBuffer;
        if (!soundBuffer.loadFromFile(filename))
            throw std::runtime_error("Unable to load '" + filename + "'");

        mSoundBuffers[key] = soundBuffer;
    }
    else
        throw std::runtime_error("Key '" + key + "' already exists");
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
