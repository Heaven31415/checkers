#pragma once

#include <memory>
#include "resources.hpp"

class SoundPlayer
{
public:
    SoundPlayer(const SoundPlayer&) = delete;
    SoundPlayer& operator=(const SoundPlayer&) = delete;

    static SoundPlayer& getInstance();
    static void playSound(const std::string& name, float volume = 100.f, float pitch = 1.0f);

private:
    SoundPlayer();

    void playSoundImpl(const std::string& name, float volume, float pitch);
    void clean();
private:
    std::vector<std::unique_ptr<sf::Sound>> mSounds;
};