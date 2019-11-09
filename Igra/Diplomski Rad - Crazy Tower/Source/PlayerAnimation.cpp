#include <PlayerAnimation.hpp>
#include <Player.hpp>
#include <Utility.hpp>

PlayerAnimation::PlayerAnimation(PlayerInfo& playerData, sf::Sprite& playerSprite, Player& pl)
	: data(playerData)
	, sprite(playerSprite)
	, player(pl)
	, isRotatingSprite(false)
	, rotateDirection(0)
{
}

void PlayerAnimation::updateSprite(sf::Time dt)
{
	time += dt;
	float timeSec = time.asSeconds();
	sf::Vector2f playerVelocity = player.getVelocity();

	setRotatingSprite(timeSec, playerVelocity);

	// No need for checking for other sprites
	if (isRotatingSprite)
	{
		return;
	}

	if (!player.isStandingOnPlatform())
	{
		setOnPlatformSprite(timeSec, playerVelocity);
	}
	else
	{
		setInAirSprite(timeSec, playerVelocity);
	}

}

void PlayerAnimation::setRotatingSprite(float timeSec, sf::Vector2f playerVelocity)
{
	if (playerVelocity.y < -1500.f && !isRotatingSprite)
	{
		isRotatingSprite = true;
		sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Rotate]);
		Utility::centerOrigin(sprite);
		if (playerVelocity.x < 0)
		{
			rotateDirection = -1;
		}
		else
		{
			rotateDirection = 1;
		}
	}

	if (isRotatingSprite)
	{
		if (timeSec < frameStep)
		{
			sprite.rotate(rotateDirection * 10.f);
		}
		else
		{
			time = sf::Time::Zero;
		}

	}
}

void PlayerAnimation::setOnPlatformSprite(float timeSec, sf::Vector2f playerVelocity)
{
	if (abs(playerVelocity.x) < 2)
	{
		sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Jump]);
	}
	else
	{
		if (playerVelocity.y < -1)
		{
			sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Jump1]);
		}
		else if (playerVelocity.y < 1)
		{
			sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Jump2]);
		}
		else
		{
			sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Jump3]);
		}
	}

}

void PlayerAnimation::setInAirSprite(float timeSec, sf::Vector2f playerVelocity)
{
	if (abs(playerVelocity.x) < 2)
	{

		if (player.playerisOnEdge())
		{
			if (timeSec < frameStep)
			{
				sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Edge1]);
			}
			else if (timeSec < 2 * frameStep)
			{
				sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Edge2]);
			}
			else
			{
				time = sf::Time::Zero;
			}
		}
		else
		{
			if (timeSec < frameStep)
			{
				sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Idle1]);
			}
			else if (timeSec < 2 * frameStep)
			{
				sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Idle2]);
			}
			else if (timeSec < 3 * frameStep)
			{
				sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Idle3]);
			}
			else
			{
				time = sf::Time::Zero;
			}
		}

	}
	else
	{
		if (timeSec < frameStep)
		{
			sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Walk1]);
		}
		else if (timeSec < 2 * frameStep)
		{
			sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Walk2]);
		}
		else if (timeSec < 3 * frameStep)
		{
			sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Walk3]);
		}
		else if (timeSec < 4 * frameStep)
		{
			sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Walk4]);
		}
		else
		{
			time = sf::Time::Zero;
		}
	}
}

void PlayerAnimation::setIdleSprite()
{
	sprite.setRotation(0);
	isRotatingSprite = false;
	if (abs(player.getVelocity().x) < 1)
	{
		sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Idle1]);
	}
	else
	{
		sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Walk1]);
	}
	Utility::centerOrigin(sprite);
}




