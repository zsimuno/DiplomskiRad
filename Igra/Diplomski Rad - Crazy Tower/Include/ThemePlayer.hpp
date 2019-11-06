#ifndef THEMEPLAYER_HPP
#define THEMEPLAYER_HPP

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>

class ThemePlayer : private sf::NonCopyable
{
public:
										ThemePlayer();

	void								play(Themes::ID theme);
	void								stop();

	void								setPaused(bool paused);
	void								setVolume(float vol);
	float								getVolume();

private:
	sf::Music							currentTheme;
	std::map<Themes::ID, std::string>	themeFiles;
	float								volume;
};

#endif // THEMEPLAYER_HPP
