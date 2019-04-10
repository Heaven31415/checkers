#pragma once

#include "common.hpp"

class Resources
{
public:
    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

    static Resources& get();

    sf::Font& font(const std::string& name);
    sf::SoundBuffer& soundBuffer(const std::string& name);
    sf::Texture& texture(const std::string& name);
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