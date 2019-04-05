#pragma once

#include "common.hpp"

class Resources
{
public:
    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

    static Resources& getInstance();
    static sf::Font& getFont(const std::string& name);
    static sf::SoundBuffer& getSoundBuffer(const std::string& name);
    static sf::Texture& getTexture(const std::string& name);
private:
    Resources();

    void loadFont(const std::string& key, const std::string& filename);
    void loadSoundBuffer(const std::string& key, const std::string& filename);
    void loadTexture(const std::string& key, const std::string& filename);

private:
    std::map<std::string, sf::Font> mFonts;
    std::map<std::string, sf::SoundBuffer> mSoundBuffers;
    std::map<std::string, sf::Texture> mTextures;
};