#ifndef  GAME_HPP
#define  GAME_HPP

#include <ResourceHolder.hpp>
#include <Player.hpp>
#include <Tower.hpp>
#include <PlayerData.hpp>
#include <StateStack.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class    Game : sf::NonCopyable
{
public:
	Game();
	void					 run();

private:
	void					processInput();
	void					update(sf::Time dt);
	void					render();

	void					registerStates();
	void					loadResources();

private:
	sf::RenderWindow		window;
	TextureHolder			textures;
	FontHolder				fonts;
	Textures::ID			currentCharacter;
	Leaderboards			leaderboards;
	SoundPlayer				soundPlayer;
	ThemePlayer				themePlayer;

	StateStack				stateStack;

	static const sf::Time	TimePerFrame;

};

#endif   // GAME_HPP
