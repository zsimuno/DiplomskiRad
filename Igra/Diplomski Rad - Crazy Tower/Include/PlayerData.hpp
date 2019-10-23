#ifndef PLAYERDATA_HPP
#define PLAYERDATA_HPP

#include <ResourceIdentifiers.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>
#include <ResourceIdentifiers.hpp>
#include <map>



struct PlayerInfo
{
	float									moveSpeed;
	float									jumpSpeed;
	std::map<Textures::ID, sf::IntRect>		playerTexturesMap;
};


PlayerInfo	initializePlayerData();

#endif // PLAYERDATA_HPP
