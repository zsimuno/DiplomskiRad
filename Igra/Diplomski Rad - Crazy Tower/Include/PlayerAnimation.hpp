#ifndef PLAYERANIMATION_HPP
#define PLAYERANIMATION_HPP

#include <SceneNode.hpp>
#include <ResourceIdentifiers.hpp>
#include <PlayerData.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <map>

class Player;

class PlayerAnimation
{

public:
							PlayerAnimation(PlayerInfo& playerData, sf::Sprite& playerSprite, Player& pl);

	void					updateSprite(sf::Time dt);
	void					setIdleSprite();

private:
	void					setRotatingSprite(float timeSec, sf::Vector2f playerVelocity);
	void					setOnPlatformSprite(float timeSec, sf::Vector2f playerVelocity);
	void					setInAirSprite(float timeSec, sf::Vector2f playerVelocity);


	sf::Sprite&				sprite;
	PlayerInfo&				data;
	Player&					player;
	sf::Time				time;
	float					frameStep = 0.2f;

	bool					isRotatingSprite;
	int						rotateDirection;
};

#endif // PLAYERANIMATION_HPP
