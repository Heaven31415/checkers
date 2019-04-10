#pragma once

#include <memory>
#include "resources.hpp"

#define ADD_SONG(path) mSongs.push_back(path);

class SoundPlayer
{
public:
    SoundPlayer(const SoundPlayer&) = delete;
    SoundPlayer& operator=(const SoundPlayer&) = delete;

    static SoundPlayer& getInstance();
    static void playSound(const std::string& name, float volume = 100.f, float pitch = 1.0f);
    static void updateMusic(sf::Time dt);
private:
    SoundPlayer();

    void playSoundImpl(const std::string& name, float volume, float pitch);
    void updateMusicImpl(sf::Time dt);
    void clean();
private:
    sf::Music mMusic;
    size_t mSongIndex;
    std::vector<std::string> mSongs;
    std::vector<std::unique_ptr<sf::Sound>> mSounds;
};