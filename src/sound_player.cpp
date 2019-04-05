#include "sound_player.hpp"

SoundPlayer::SoundPlayer()
: mSounds{}
{
    mSounds.reserve(32);
}

SoundPlayer& SoundPlayer::getInstance()
{
    static SoundPlayer instance;
    return instance;
}

void SoundPlayer::playSound(const std::string& name, float volume, float pitch)
{
    getInstance().playSoundImpl(name, volume, pitch);
}

void SoundPlayer::playSoundImpl(const std::string& name, float volume, float pitch)
{
    auto sound = std::make_unique<sf::Sound>();
    sound->setBuffer(Resources::getSoundBuffer(name));
    sound->setVolume(volume);
    sound->setPitch(pitch);
    sound->play();

    mSounds.push_back(std::move(sound));

    clean();
}

void SoundPlayer::clean()
{
    mSounds.erase(
        std::remove_if(
            mSounds.begin(), 
            mSounds.end(), 
            [](const std::unique_ptr<sf::Sound>& sound) { return sound->getStatus() == sf::SoundSource::Stopped; }
        ), 
        mSounds.end()
    );
}
