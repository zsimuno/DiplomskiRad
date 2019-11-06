#include <Player.hpp>
#include <ResourceHolder.hpp>
#include <Utility.hpp>
#include <Platforms.hpp>
#include <Tower.hpp>
#include <iostream>




Player::Player(State::Context& context, Platforms& towerPlatforms, sf::FloatRect& bounds, Tower& tower)
	: sprite(context.textures->get(*context.currentCharacterID))
	, data(initializePlayerData())
	, playerVelocity(0, 0)
	, mirroredSprite(false)
	, animation(data, sprite, *this)
	, platforms(towerPlatforms)
	, currentPlatformBounds(0.f, 0.f, 0.f, 0.f)
	, inCombo(false)
	, currentCombo(0)
	, previousPlatformFloor(Platforms::startingPlatform)
	, maxCombo(0)
	, isOnPlatform(true)
	, currentBounds(bounds)
	, tower(tower)
	, context(context)
{
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
	animation.setIdle();
	currentCombo = 0;
	maxCombo = 0;
	previousPlatformFloor = Platforms::startingPlatform;
}

void Player::handleEvent()
{
}

void Player::handleRealtimeInput()
{
	if (isOnPlatform && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		playerVelocity.y -= data.jumpSpeed + 1.1f * abs(playerVelocity.x);
		std::cout << std::to_string(playerVelocity.y) << std::endl;
		isOnPlatform = false;
		if (playerVelocity.y > -1000.f)
		{
			context.soundPlayer->play(Sounds::ID::Jump1);
		} 
		else if (playerVelocity.y > -1500.f)
		{
			context.soundPlayer->play(Sounds::ID::Jump2);
		} 
		else
		{
			context.soundPlayer->play(Sounds::ID::Jump3);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		playerVelocity.x -= data.moveSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		playerVelocity.x += data.moveSpeed;
}

void Player::setVelocity(sf::Vector2f v)
{
	playerVelocity = v;
}

void Player::addVelocity(sf::Vector2f v)
{
	playerVelocity += v;
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
	if (previousPlatformFloor < plat - 1)
	{
		inCombo = true;
		currentCombo += plat - previousPlatformFloor;
	}
	else
	{
		endCombo();
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
	animation.setIdle();

	this->setPosition(this->getPosition().x, platPos.y - getBounds().height - getBounds().top);
}

bool Player::isStandingOnPlatform() const
{
	return isOnPlatform;
}

Platforms& Player::getPlatforms()
{
	return platforms;
}

sf::FloatRect Player::getCurrentPlatformBounds()
{
	return currentPlatformBounds;
}

int Player::getPlatformNumber()
{
	return previousPlatformFloor;
}

int Player::getCombo()
{
	return currentCombo;
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
	tower.drawComboText(currentCombo);
	currentCombo = 0;
}


void Player::updateCurrent(sf::Time dt)
{
	
	float dtAsSeconds = dt.asSeconds();

	playerVelocity.x *= 55.f * dtAsSeconds;

	this->handleRealtimeInput();

	if (!isOnPlatform)
	{
		playerVelocity.y += data.fallSpeed;
		platforms.isOnPlatform(*this, dtAsSeconds);
	}
	else if (currentPlatformBounds.width != 0.f)
	{
		sf::FloatRect playerRect(sf::Vector2f(getPosition().x + getBounds().left, getPosition().y + getBounds().top),
			sf::Vector2f(getBounds().width, getBounds().height));
		// Is player falling of the platform
		if (!(playerRect.left + playerRect.width > currentPlatformBounds.left&&
			playerRect.left < currentPlatformBounds.left + currentPlatformBounds.width))
		{
			isOnPlatform = false;
			endCombo();
		}
	}

	animation.updateSprite(dt);

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

