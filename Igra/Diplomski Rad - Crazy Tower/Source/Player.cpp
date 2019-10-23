#include <Player.hpp>
#include <ResourceHolder.hpp>
#include <Utility.hpp>
#include <PlayerData.hpp>

Player::Player(const TextureHolder& textures, float* scrollSpeed)
	: sprite(textures.get(Textures::ID::Character)),
	screenScrollSpeed(scrollSpeed),
	data(initializePlayerData()),
	playerVelocity(0,0),
	mirroredSprite(false)
{
	Utility::centerOrigin(sprite);
	setVelocity(sf::Vector2f(data.moveSpeed, *screenScrollSpeed));
	sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Idle1]);
	sprite.scale(1.5, 1.5);
}

void Player::handleEvent(const sf::Event& event)
{
}

void Player::handleRealtimeInput()
{
}

void Player::setVelocity(sf::Vector2f v)
{
	playerVelocity = v;
}

void Player::addVelocity(sf::Vector2f v)
{
	playerVelocity += v;
}

sf::Vector2f Player::getVelocity()
{
	return playerVelocity;
}


void Player::updateCurrent(sf::Time dt)
{
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		playerVelocity.y -= data.jumpSpeed;



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		playerVelocity.x -= data.moveSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		playerVelocity.x += data.moveSpeed;

	playerVelocity.x *= 0.9;

	move(playerVelocity * dt.asSeconds());

	Textures::ID selectedID;
	if (abs(playerVelocity.x) < 1) 
	{
		if (playerVelocity.y != 0)
		{
			selectedID = Textures::ID::Jump;
		} else
		{
			selectedID = Textures::ID::Idle1;
		}
	} else
	{
		if (playerVelocity.y != 0)
		{
			selectedID = Textures::ID::Jump1;
		}
		else
		{
			selectedID = Textures::ID::Walk1;
		}
		
	} 

	sprite.setTextureRect(data.playerTexturesMap[selectedID] );
	Utility::centerOrigin(sprite);

	if ((playerVelocity.x < -1 && !mirroredSprite) || (playerVelocity.x > 1 && mirroredSprite))
	{
		sprite.scale(-1.f, 1.f);
		mirroredSprite = !mirroredSprite;
	}
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}


