#ifndef PLAYERANIMATION_HPP
#define PLAYERANIMATION_HPP


#include <SceneNode.hpp>
#include <ResourceIdentifiers.hpp>
#include <PlayerData.hpp>
#include <Player.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include <map>

class PlayerAnimation
{

public:
	PlayerAnimation(PlayerInfo& playerData, sf::Sprite& playerSprite, Player& pl);

	void					updateSprite(sf::Time dt);

private:
	sf::Sprite&				sprite;
	PlayerInfo&				data;
	Player&					player;
	sf::Time				time;
	float					frameStep = 0.2f;

};

#endif // PLAYERANIMATION_HPP
