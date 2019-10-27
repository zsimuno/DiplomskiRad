#include <Player.hpp>
#include <ResourceHolder.hpp>
#include <Utility.hpp>
#include <PlayerAnimation.hpp>
#include <Platforms.hpp>
#include <iostream>

Player::Player(const TextureHolder& textures, float& scrollSpeed, Platforms& towerPlatforms)
	: sprite(textures.get(Textures::ID::Character)),
	screenScrollSpeed(scrollSpeed),
	data(initializePlayerData()),
	playerVelocity(0, 0),
	mirroredSprite(false),
	animation(new PlayerAnimation(data, sprite, *this)),
	platforms(towerPlatforms),
	currentPlatform(nullptr),
	context(data, *this),
	inAirState(context),
	onPlatformState(context),
	currentStateID(PlayerStates::ID::OnPlatform)
{
	
	setVelocity(sf::Vector2f(data.moveSpeed, screenScrollSpeed));
	sprite.setTextureRect(data.playerTexturesMap[Textures::ID::Idle1]);
	sprite.setScale(sf::Vector2f(1.5, 1.5));
	Utility::centerOrigin(sprite);
}

void Player::handleEvent()
{
}

void Player::handleRealtimeInput()
{
	if (isOnPlatform && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		playerVelocity.y -= data.jumpSpeed;
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

float Player::getWorldScrollSpeed() const
{
	return screenScrollSpeed;
}

void Player::setOnPlatform(Platform* platform)
{
	currentPlatform = platform;
	isOnPlatform = true;
	playerVelocity.y = 0.0f;
	animation->setIdle();

	this->setPosition(this->getPosition().x , currentPlatform->getBounds().top - getBounds().height - getBounds().top - 1);
	
}

bool Player::isStandingOnPlatform() const
{
	return isOnPlatform;
}

void Player::changeState()
{
	if (currentStateID == PlayerStates::ID::InAir)
	{
		currentState = &onPlatformState;
		currentStateID = PlayerStates::ID::OnPlatform;
	} 
	else
	{
		currentState = &inAirState;
		currentStateID = PlayerStates::ID::InAir;
	}
}

const Platforms& Player::getPlatforms()
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

	platforms.isOnPlatform(*this, dtAsSeconds);

	this->handleRealtimeInput();

	if (!isOnPlatform)
	{
		playerVelocity.y += data.fallSpeed;
	}
	else if(currentPlatform != nullptr)
	{
		sf::FloatRect playerRect(sf::Vector2f(getPosition().x + getBounds().left, getPosition().y + getBounds().top),
			sf::Vector2f(getBounds().width, getBounds().height));
		if (!(playerRect.left + playerRect.width > currentPlatform->getBounds().left &&
			playerRect.left < currentPlatform->getBounds().left + currentPlatform->getBounds().width))
		{
			isOnPlatform = false;
		}
	}

	move((playerVelocity + sf::Vector2f(0.f, screenScrollSpeed)) * dtAsSeconds);

	animation->updateSprite(dt);

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




