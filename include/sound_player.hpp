#pragma once

#include "resources.hpp"

class SoundPlayer
{
public:
    SoundPlayer();
    ~SoundPlayer();

    void playSound(std::string name, float volume = 100.f, float pitch = 1.0f);
    void clean();
private:
    std::vector<sf::Sound*> mSounds;
};