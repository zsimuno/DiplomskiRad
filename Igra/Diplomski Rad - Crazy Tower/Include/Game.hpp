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

	void					updateStatistics(sf::Time elapsedTime);
	void					registerStates();

private:
	sf::RenderWindow		window;
	Tower					tower;
	TextureHolder			textures;
	FontHolder				fonts;
	StateStack				stateStack;

	static const sf::Time	TimePerFrame;

	

	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	int						mStatisticsNumFrames;

};

#endif   // GAME_HPP
