#include <PlayerAnimation.hpp>



PlayerAnimation::PlayerAnimation(PlayerInfo& playerData, sf::Sprite& playerSprite, Player& pl)
	: data(playerData),
	sprite(playerSprite),
	player(pl)
{
}

void PlayerAnimation::updateSprite(sf::Time dt)
{
	time += dt;
	float timeSec = time.asSeconds(); 
	sf::Vector2f playerVelocity = player.getVelocity();

	if (abs(playerVelocity.x) < 1)
	{
		if (playerVelocity.y != 0)
		{
			sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Jump]);
		}
		else
		{
			if (timeSec < frameStep)
			{
				sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Idle1]);
			}
			else if (timeSec < 2 * frameStep)
			{
				sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Idle2]);
			}
			else if (timeSec < 3 * frameStep)
			{
				sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Idle3]);
			}
			else
			{
				time = sf::Time::Zero;
			}

		}
	}
	else
	{
		if (!player.standingOnPlatform())
		{
			if (playerVelocity.y < -1)
			{
				sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Jump1]);
			}
			else if (playerVelocity.y < 1)
			{
				sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Jump2]);
			}
			else
			{
				sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Jump3]);
			}


		}
		else
		{
			if (timeSec < frameStep)
			{
				sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Walk1]);
			}
			else if (timeSec < 2 * frameStep)
			{
				sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Walk2]);
			}
			else if (timeSec < 3 * frameStep)
			{
				sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Walk3]);
			}
			else if (timeSec < 4 * frameStep)
			{
				sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Walk4]);
			}
			else
			{
				time = sf::Time::Zero;
			}
		}
	}
}

void PlayerAnimation::setIdle()
{
	if (abs(player.getVelocity().x) < 1)
	{
		sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Idle1]);
	}
	else
	{
		sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Walk1]);
	}
}


