#include <PlayerData.hpp>
#include <ResourceIdentifiers.hpp>

PlayerInfo initializePlayerData()
{
	PlayerInfo data;

	data.jumpSpeed = 1050.f;
	data.moveSpeed = 100.f;
	data.fallSpeed = 50.0f;
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Idle1, sf::IntRect(2, 4, 28, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Idle2, sf::IntRect(306, 4, 30, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Idle3, sf::IntRect(339, 4, 30, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Walk1, sf::IntRect(35, 4, 28, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Walk2, sf::IntRect(68, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Walk3, sf::IntRect(102, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Walk4, sf::IntRect(136, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Jump,  sf::IntRect(272, 4, 29, 58)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Jump1, sf::IntRect(170, 4, 28, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Jump2, sf::IntRect(204, 4, 28, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Jump3, sf::IntRect(238, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Shock, sf::IntRect(372, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Rotate,sf::IntRect(406, 4, 43, 60)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Edge1, sf::IntRect(497, 4, 37, 50)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Edge2, sf::IntRect(455, 4, 36, 50)));
	
	return data;
}
