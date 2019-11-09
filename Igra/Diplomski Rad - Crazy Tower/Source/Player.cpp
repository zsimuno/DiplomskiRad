#include <Player.hpp>
#include <ResourceHolder.hpp>
#include <Utility.hpp>
#include <Platforms.hpp>
#include <Tower.hpp>

#include <iostream>

Player::Player(State::Context& context, Platforms& towerPlatforms, Tower& tower)
	: context(context)
	, platforms(towerPlatforms)
	, tower(tower)
	, sprite(context.textures->get(*context.currentCharacterID))
	, data(initializePlayerData())
	, mirroredSprite(false)
	, animation(data, sprite, *this)
	, isOnEdge(false)
{
	initialize();

	sprite.setTextureRect(data.playerTexturesMap[PlayerSprite::ID::Idle1]);
	sprite.setScale(sf::Vector2f(1.5, 1.5));
	Utility::centerOrigin(sprite);
}

void Player::initialize()
{
	playerVelocity = sf::Vector2f(0, 0);
	currentPlatformBounds = sf::FloatRect(0.f, 0.f, 0.f, 0.f);
	inCombo = false;
	isOnPlatform = true;
	animation.setIdleSprite();
	currentCombo = 0;
	maxCombo = 0;
	previousPlatformFloor = Platforms::startingPlatform;
	highestPlatform = Platforms::startingPlatform;
}


void Player::handleRealtimeInput()
{
	if (isOnPlatform && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		playerVelocity.y -= data.jumpSpeed + 1.2f * abs(playerVelocity.x);
		isOnPlatform = false;
		if (playerVelocity.y > -1400.f)
		{
			context.soundPlayer->play(Sounds::ID::Jump1);
		} 
		else if (playerVelocity.y > -1800.f)
		{
			context.soundPlayer->play(Sounds::ID::Jump2);
		} 
		else
		{
			context.soundPlayer->play(Sounds::ID::Jump3);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerVelocity.x = playerVelocity.x * data.moveAcceleration - (data.maxMoveSpeed * (1 - data.moveAcceleration));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerVelocity.x = playerVelocity.x * data.moveAcceleration + (data.maxMoveSpeed * (1 - data.moveAcceleration));
	}
	else
	{
		playerVelocity.x = playerVelocity.x * data.moveAcceleration;
	}

	// Limit movement
	if (playerVelocity.x > data.maxMoveSpeed)
	{
		playerVelocity.x = data.maxMoveSpeed;
	}
	else if (playerVelocity.x < -data.maxMoveSpeed)
	{
		playerVelocity.x = -data.maxMoveSpeed;
	}

}

void Player::setVelocity(sf::Vector2f v)
{
	playerVelocity = v;
}

sf::Vector2f Player::getVelocity() const
{
	return playerVelocity;
}

sf::FloatRect Player::getBounds() const
{
	return sprite.getGlobalBounds();
}

void Player::setOnPlatform(Platform* platform)
{
	// Combos happen if player jumps more than one platform. Otherwise the combo resets.
	int plat = platform->getPlatformNumber();
	if (previousPlatformFloor < plat - 1 || previousPlatformFloor == plat)
	{
		inCombo = true;
		currentCombo += plat - previousPlatformFloor;
	}
	else
	{
		endCombo();
	}

	if (plat > highestPlatform)
	{
		highestPlatform = plat;
	}

	// Set the player on the platform and save current platform data
	sf::FloatRect platBounds = platform->getBounds();
	sf::Vector2f platPos = platform->getWorldPosition();
	currentPlatformBounds = platBounds;
	currentPlatformBounds.left = platPos.x;
	currentPlatformBounds.top = platPos.y;
	previousPlatformFloor = plat;
	isOnPlatform = true;
	playerVelocity.y = 0.0f;
	animation.setIdleSprite();

	this->setPosition(this->getPosition().x, platPos.y - getBounds().height - getBounds().top);

	// If player is set left or right of the platform (happens while rotating)
	sf::FloatRect playerRect(sf::Vector2f(getPosition().x + getBounds().left, getPosition().y + getBounds().top),
		sf::Vector2f(getBounds().width, getBounds().height));

	if (playerRect.left + playerRect.width < currentPlatformBounds.left)
	{
		this->setPosition(currentPlatformBounds.left - playerRect.width /4 , this->getPosition().y );
	}
	else if (playerRect.left > currentPlatformBounds.left + currentPlatformBounds.width)
	{
		this->setPosition(currentPlatformBounds.left + currentPlatformBounds.width + playerRect.width / 4, this->getPosition().y );
	}

}

bool Player::isStandingOnPlatform() const
{
	return isOnPlatform;
}

Platforms& Player::getPlatforms()
{
	return platforms;
}

sf::FloatRect Player::getCurrentPlatformBounds() const
{
	return currentPlatformBounds;
}

int Player::getPlatformNumber()
{
	return previousPlatformFloor;
}

int Player::getHighestPlatform()
{
	return highestPlatform;
}

int Player::getCombo()
{
	return currentCombo;
}

int Player::getHighestCombo()
{
	return maxCombo;
}

bool Player::isInCombo()
{
	return inCombo;
}

void Player::endCombo()
{
	inCombo = false;
	if (currentCombo > maxCombo)
	{
		maxCombo = currentCombo;
	}
	tower.drawComboText((float)currentCombo);
	currentCombo = 0;
}

bool Player::playerisOnEdge()
{
	return isOnEdge;
}

sf::FloatRect Player::getPrevFrameBounds() const
{
	return prevFrameBounds;
}


void Player::updateCurrent(sf::Time dt)
{
	float dtAsSeconds = dt.asSeconds();

	this->handleRealtimeInput();

	animation.updateSprite(dt);

	if (!isOnPlatform)
	{
		playerVelocity.y += data.fallSpeed;
		platforms.isPlayerOnPlatform(*this, dtAsSeconds);

		sf::FloatRect bounds(getBounds());
		prevFrameBounds = sf::FloatRect(getPosition().x - bounds.width / 2, getPosition().y - bounds.height / 2, bounds.width, bounds.height);
	}
	else if (currentPlatformBounds.width != 0.f)
	{
		// Is player falling of the platform
		sf::FloatRect playerRect(sf::Vector2f(getPosition().x + getBounds().left, getPosition().y + getBounds().top),
			sf::Vector2f(getBounds().width, getBounds().height));
		
		if (!(playerRect.left + playerRect.width > currentPlatformBounds.left&&
			playerRect.left < currentPlatformBounds.left + currentPlatformBounds.width))
		{
			isOnPlatform = false;
		}

		// Is player standing on the edge
		if (abs(playerVelocity.x) < 2  
			&& (playerRect.left   < currentPlatformBounds.left - 10.f 
			|| playerRect.left + playerRect.width  > currentPlatformBounds.left + currentPlatformBounds.width + 10.f) 
			&& getPlatformNumber() % 50 != 0 )
		{
			// Play the sound only first time
			if (!isOnEdge)
			{
				context.soundPlayer->play(Sounds::ID::Ledge);
			}
			isOnEdge = true;
		}
		else
		{
			isOnEdge = false;
		}
	}


	// Mirror sprite depending on moving direction
	if ((playerVelocity.x < -1 && !mirroredSprite) || (playerVelocity.x > 1 && mirroredSprite))
	{
		sprite.scale(-1.f, 1.f);
		mirroredSprite = !mirroredSprite;
	}

	move(playerVelocity * dtAsSeconds);

}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

