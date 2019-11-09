#ifndef PLAYERDATA_HPP
#define PLAYERDATA_HPP

#include <ResourceIdentifiers.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>
#include <map>

struct PlayerInfo
{
	float										moveSpeed;
	float										jumpSpeed;
	float										fallSpeed;
	std::map<PlayerSprite::ID, sf::IntRect>		playerTexturesMap;
};


PlayerInfo	initializePlayerData();

#endif // PLAYERDATA_HPP
