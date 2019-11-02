#include <Player.hpp>
#include <ResourceHolder.hpp>
#include <Utility.hpp>
#include <Platforms.hpp>
#include <iostream>


Player::Player(const TextureHolder& textures, Platforms& towerPlatforms, sf::FloatRect& bounds)
	: sprite(textures.get(Textures::ID::Character))
	, data(initializePlayerData())
	, playerVelocity(0, 0)
	, mirroredSprite(false)
	, animation(data, sprite, *this)
	, platforms(towerPlatforms)
	, currentPlatform(nullptr)
	, isInCombo(false)
	, currentCombo(0)
	, maxCombo(0)
	, isOnPlatform(true)
	, currentBounds(bounds)
{
	sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Idle1]);
	sprite.setScale(sf::Vector2f(1.5, 1.5));
	Utility::centerOrigin(sprite);
}

void Player::initialize()
{
	playerVelocity = sf::Vector2f(0, 0);
	currentPlatform = nullptr;
	isInCombo = false;
	isOnPlatform = true;
	animation.setIdle();
	currentCombo = 0;
	maxCombo = 0;
}

void Player::handleEvent()
{
}

void Player::handleRealtimeInput()
{
	if (isOnPlatform && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		playerVelocity.y -= data.jumpSpeed + abs(playerVelocity.x);
		isOnPlatform = false;
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
	currentPlatform = platform;
	isOnPlatform = true;
	playerVelocity.y = 0.0f;
	animation.setIdle();

	this->setPosition(this->getPosition().x, currentPlatform->getBounds().top - getBounds().height - getBounds().top);
}

bool Player::isStandingOnPlatform() const
{
	return isOnPlatform;
}

Platforms& Player::getPlatforms()
{
	return platforms;
}

Platform* Player::getCurrentPlatform()
{
	return currentPlatform;
}

void Player::updateCurrent(sf::Time dt)
{
	playerVelocity.x *= 0.9f;
	float dtAsSeconds = dt.asSeconds();

	this->handleRealtimeInput();

	if (!isOnPlatform)
	{
		playerVelocity.y += data.fallSpeed;
		platforms.isOnPlatform(*this, dtAsSeconds);
	}
	else if (currentPlatform != nullptr)
	{
		sf::FloatRect playerRect(sf::Vector2f(getPosition().x + getBounds().left, getPosition().y + getBounds().top),
			sf::Vector2f(getBounds().width, getBounds().height));
		// Is player falling of the platform
		if (!(playerRect.left + playerRect.width > currentPlatform->getBounds().left&&
			playerRect.left < currentPlatform->getBounds().left + currentPlatform->getBounds().width))
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

void Player::endCombo()
{
	isInCombo = false;
	if (currentCombo > maxCombo)
	{
		maxCombo = currentCombo;
	}
	currentCombo = 0;
}
