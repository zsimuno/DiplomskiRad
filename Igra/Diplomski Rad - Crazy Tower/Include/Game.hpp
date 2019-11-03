#ifndef  GAME_HPP
#define  GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <Player.hpp>
#include <ResourceHolder.hpp>
#include <Tower.hpp>
#include <PlayerData.hpp>
#include <StateStack.hpp>

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
	StateStack				stateStack;

	static const sf::Time	TimePerFrame;

};

#endif   // GAME_HPP
