#include "sound_player.hpp"

SoundPlayer::SoundPlayer()
: mSounds{}
{
}

SoundPlayer::~SoundPlayer()
{
    for (size_t i = 0; i < mSounds.size(); i++)
        delete mSounds[i];
}

void SoundPlayer::playSound(std::string name, float volume, float pitch)
{
    sf::Sound* sound = new sf::Sound{};
    sound->setBuffer(Resources::getSoundBuffer(name));
    sound->setVolume(volume);
    sound->setPitch(pitch);
    sound->play();

    mSounds.push_back(sound);

    clean();
}

void SoundPlayer::clean()
{
    std::vector<sf::Sound*>::iterator it = mSounds.begin();

    while (it != mSounds.end())
    {
        if ((*it)->getStatus() == sf::SoundSource::Stopped)
        {
            delete *it;
            it = mSounds.erase(it);
        }
        else
            it++;
    }
}
