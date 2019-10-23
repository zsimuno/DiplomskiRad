#include <PlayerData.hpp>
#include <ResourceIdentifiers.hpp>

PlayerInfo initializePlayerData()
{
	PlayerInfo data;

	data.jumpSpeed = 20.f;
	data.moveSpeed = 30.f;
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Idle1, sf::IntRect(1, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Idle2, sf::IntRect(305, 4, 32, 52)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Idle3, sf::IntRect(338, 4, 32, 52)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Walk1, sf::IntRect(34, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Walk2, sf::IntRect(67, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Walk3, sf::IntRect(101, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Walk4, sf::IntRect(134, 4, 29, 52)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Jump,  sf::IntRect(271, 4, 30, 58)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Jump1, sf::IntRect(169, 4, 29, 56)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Jump2, sf::IntRect(203, 4, 29, 53)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Jump3, sf::IntRect(237, 4, 30, 55)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Shock, sf::IntRect(371, 4, 30, 52)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Rotate,sf::IntRect(405, 4, 44, 60)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Edge1, sf::IntRect(496, 4, 40, 52)));
	data.playerTexturesMap.insert(std::make_pair(Textures::ID::Edge2, sf::IntRect(454, 4, 37, 52)));
	

	return data;
}
