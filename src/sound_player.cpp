#include "sound_player.hpp"

SoundPlayer::SoundPlayer()
: mMusic{}
, mSongIndex{}
, mSongs{}
, mSounds{}
{
    ADD_SONG("resources/Decision.ogg");
    ADD_SONG("resources/Forest.ogg");
    ADD_SONG("resources/JourneyToTheEastRocks.ogg");
    ADD_SONG("resources/Nature.ogg");
    ADD_SONG("resources/WoodlandFantasy.ogg");
    ADD_SONG("resources/Woods.ogg");

    mSounds.reserve(32);
}

SoundPlayer& SoundPlayer::get()
{
    static SoundPlayer instance;
    return instance;
}

void SoundPlayer::playSound(const std::string& name, float volume, float pitch)
{
    auto sound = std::make_unique<sf::Sound>();
    sound->setBuffer(Resources::getSoundBuffer(name));
    sound->setVolume(volume);
    sound->setPitch(pitch);
    sound->play();

    mSounds.push_back(std::move(sound));

    clean();
}

void SoundPlayer::updateMusic()
{
    if (mMusic.getStatus() != sf::SoundSource::Playing)
    {
        mSongIndex = (mSongIndex + 1) % mSongs.size();
        if (!mMusic.openFromFile(mSongs[mSongIndex]))
            throw std::runtime_error("Unable to load Music because openFromFile method failed");
        mMusic.setVolume(0.f);
        mMusic.play();
    }

    float progress = (mMusic.getPlayingOffset() / mMusic.getDuration()) * 100.f;

    if (progress < 10.f)
        mMusic.setVolume(progress / 10.f * 100.f);
    else if (progress > 90.f)
        mMusic.setVolume(100.f - ((progress - 90.f) / 10.f * 100.f));
    else
        mMusic.setVolume(100.f);
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