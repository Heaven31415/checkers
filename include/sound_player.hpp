#pragma once

#include <memory>
#include "resources.hpp"

#define ADD_SONG(path) mSongs.push_back(path);

class SoundPlayer
{
public:
    SoundPlayer(const SoundPlayer&) = delete;
    SoundPlayer& operator=(const SoundPlayer&) = delete;

    static SoundPlayer& get();

    void playSound(const std::string& name, float volume, float pitch);
    void updateMusic();
    void clean();
private:
    SoundPlayer();
private:
    sf::Music mMusic;
    size_t mSongIndex;
    std::vector<std::string> mSongs;
    std::vector<std::unique_ptr<sf::Sound>> mSounds;
};