#include <SoundPlayer.hpp>

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>

SoundPlayer::SoundPlayer()
	: soundHolder()
	, volume(100.f)
{
	loadSounds();
}

void SoundPlayer::play(Sounds::ID soundID)
{
	// TODO: game crashing on this push_back
	sounds.push_back(sf::Sound());
	sf::Sound& sound = sounds.back();

	sound.setBuffer(soundHolder.get(soundID));
	sound.setVolume(volume);

	sound.play();
}

void SoundPlayer::removeStoppedSounds()
{
	sounds.remove_if([](const sf::Sound& sound)
		{
			return sound.getStatus() == sf::Sound::Stopped;
		});
}

void SoundPlayer::setVolume(float vol)
{
	volume = vol;
}

float SoundPlayer::getVolume()
{
	return volume;
}

void SoundPlayer::loadSounds()
{
	soundHolder.load(Sounds::ID::Good, "Media/Sound/good.wav");
	soundHolder.load(Sounds::ID::Sweet, "Media/Sound/sweet.wav");
	soundHolder.load(Sounds::ID::Great, "Media/Sound/great.wav");
	soundHolder.load(Sounds::ID::Super, "Media/Sound/super.wav");
	soundHolder.load(Sounds::ID::Wow, "Media/Sound/wow.wav");
	soundHolder.load(Sounds::ID::Amazing, "Media/Sound/amazing.wav");
	soundHolder.load(Sounds::ID::Extreme, "Media/Sound/extreme.wav");
	soundHolder.load(Sounds::ID::Fantastic, "Media/Sound/fantastic.wav");
	soundHolder.load(Sounds::ID::Splendid, "Media/Sound/splendid.wav");
	soundHolder.load(Sounds::ID::NoWay, "Media/Sound/no_way.wav");
	soundHolder.load(Sounds::ID::HurryUp, "Media/Sound/hurry_up.wav");
	soundHolder.load(Sounds::ID::Hi, "Media/Sound/hi.wav");
	soundHolder.load(Sounds::ID::Jump1, "Media/Sound/jump1.wav");
	soundHolder.load(Sounds::ID::Jump2, "Media/Sound/jump2.wav");
	soundHolder.load(Sounds::ID::Jump3, "Media/Sound/jump3.wav");
	soundHolder.load(Sounds::ID::Alright, "Media/Sound/alright.wav");
	soundHolder.load(Sounds::ID::Falling, "Media/Sound/falling.wav");
	soundHolder.load(Sounds::ID::Ledge, "Media/Sound/edge.wav");
	soundHolder.load(Sounds::ID::MenuMove, "Media/Sound/menu_option.wav");
	soundHolder.load(Sounds::ID::MenuSelect, "Media/Sound/menu_select.wav");
	soundHolder.load(Sounds::ID::TryAgain, "Media/Sound/try_again.wav");
	soundHolder.load(Sounds::ID::Applause, "Media/Sound/applause.wav");
	soundHolder.load(Sounds::ID::Pause, "Media/Sound/pause.wav");
}
