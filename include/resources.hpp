#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Resources
{
public:
    Resources();
    sf::SoundBuffer& getSoundBuffer(std::string name);
    sf::Texture& getTexture(std::string name);
    sf::Font& getFont();

private:
    void loadSoundBuffer(std::string key, std::string filename);
    void loadTexture(std::string key, std::string filename);

    std::map<std::string, sf::SoundBuffer> mSoundBuffers;
    std::map<std::string, sf::Texture> mTextures;
    sf::Font mFont;
};