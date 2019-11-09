#ifndef SOUNDPLAYER_HPP
#define SOUNDPLAYER_HPP

#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <list>

class SoundPlayer
{
public:
							SoundPlayer();
	void					play(Sounds::ID soundID);

	void					removeStoppedSounds();

	void					setVolume(float vol);
	float					getVolume();

	void					loadSounds();
private:

	SoundHolder				soundHolder;
	sf::Sound				sound;
	std::list<sf::Sound>	sounds;
	float					volume;
};

#endif // SOUNDPLAYER_HPP