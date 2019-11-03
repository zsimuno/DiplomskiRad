#include <PlayerData.hpp>
#include <ResourceIdentifiers.hpp>

PlayerInfo initializePlayerData()
{
	PlayerInfo data;

	data.jumpSpeed = 1150.f;
	data.moveSpeed = 100.f;
	data.fallSpeed = 60.0f;
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Idle1, sf::IntRect(2, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Idle2, sf::IntRect(306, 4, 31, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Idle3, sf::IntRect(339, 4, 31, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Walk1, sf::IntRect(34, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Walk2, sf::IntRect(67, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Walk3, sf::IntRect(101, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Walk4, sf::IntRect(135, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Jump,  sf::IntRect(271, 4, 30, 58)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Jump1, sf::IntRect(169, 4, 29, 56)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Jump2, sf::IntRect(203, 4, 29, 53)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Jump3, sf::IntRect(237, 4, 30, 55)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Shock, sf::IntRect(371, 4, 30, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Rotate,sf::IntRect(405, 4, 44, 60)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Edge1, sf::IntRect(496, 4, 40, 52)));
	data.playerTexturesMap.insert(std::make_pair(PlayerSprite::ID::Edge2, sf::IntRect(454, 4, 37, 52)));
	
	return data;
}
