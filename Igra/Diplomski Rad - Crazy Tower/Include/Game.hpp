#ifndef  GAME_HPP
#define  GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <Player.hpp>
#include <ResourceHolder.hpp>
#include <World.hpp>
#include <PlayerData.hpp>

class    Game : sf::NonCopyable
{
public:
	Game();
	void run();

private:
	void processInput();
	void update(sf::Time dt);
	void render();

	void					updateStatistics(sf::Time elapsedTime);

private:
	sf::RenderWindow		mWindow;
	World					mWorld;
	TextureHolder			mTextures;

	static const sf::Time	TimePerFrame;

	sf::Font				mFont;

	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	int						mStatisticsNumFrames;

};

#endif   // GAME_HPP
