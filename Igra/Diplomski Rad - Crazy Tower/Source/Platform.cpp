#include <Platform.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/Font.hpp>
#include <Platforms.hpp>
#include <iostream>

Platform::Platform(int floorNumber, sf::FloatRect towerBounds, State::Context context, int previousPlatform)
	: platformRect()
	, platformNumber(floorNumber)
	, floorNumberText(std::to_string(floorNumber), context.fonts->get(Fonts::ID::Main))
	, platformSprite()
{
	platformRect.top = (float) previousPlatform - Platform::platformHeight - 100;
	platformRect.height = platformHeight;

	// Set the platform texture depending on the floor
	Textures::ID selectedTextureID;

	if (floorNumber < 100)
	{
		selectedTextureID = Textures::ID::Floor1;
		platformRect.width = minPlatformWidth + rand() % (int)(towerBounds.width * 0.3);
	}
	else if (floorNumber < 200)
	{
		selectedTextureID = Textures::ID::Floor2;
		platformRect.width = minPlatformWidth + rand() % (int)(towerBounds.width * 0.2);
	}
	else if (floorNumber < 300)
	{
		selectedTextureID = Textures::ID::Floor3;
		platformRect.width = minPlatformWidth + rand() % (int)(towerBounds.width * 0.1);
	}
	else if (floorNumber < 400)
	{
		selectedTextureID = Textures::ID::Floor4;
		platformRect.width = minPlatformWidth + rand() % (int)(towerBounds.width * 0.1);
	}
	else if (floorNumber < 500)
	{
		selectedTextureID = Textures::ID::Floor5;
		platformRect.width = minPlatformWidth + rand() % (int)(towerBounds.width * 0.1);
	}
	else
	{
		selectedTextureID = Textures::ID::Floor6;
		platformRect.width = minPlatformWidth;
	}

	platformRect.left =(int)( rand() % (int)(towerBounds.width - platformRect.width));

	if (floorNumber % 50 == 0)
	{
		platformRect.left = 0.f;
		platformRect.width = towerBounds.width;

		if (platformNumber == Platforms::startingPlatform)
		{
			platformRect.top = towerBounds.top + towerBounds.height - Platform::platformHeight;
		}

	}

	this->setPosition(platformRect.left, platformRect.top);

	// Draw the texture of the platform
	sf::Texture& texture = context.textures->get(selectedTextureID);
	sf::IntRect textureRect(platformRect);
	texture.setRepeated(true);
	platformSprite.setPosition(sf::Vector2f(0.f, 0.f));
	platformSprite.setTexture(texture);
	platformSprite.setTextureRect(textureRect);

	// Only display floor on floors that are divisible by 10
	if (platformNumber % 10 != 0)
	{
		return;
	}

	floorNumberText.setCharacterSize(20);
	floorNumberText.setFillColor(sf::Color::White);
	Utility::centerOrigin(floorNumberText);
	floorNumberText.setPosition(platformRect.width / 2,  platformRect.height - 10);

	numberRect.setSize(sf::Vector2f(50, 30));
	Utility::centerOrigin(numberRect);
	numberRect.setPosition(platformRect.width / 2, platformRect.height - 10);
	numberRect.setFillColor(sf::Color(0x795548FF));
	numberRect.setOutlineThickness(-1);
	numberRect.setOutlineColor(sf::Color::Black);
}

sf::FloatRect Platform::getBounds()
{
	return platformRect;
}

bool Platform::isOnPlatform(Player& player, float dtAsSeconds)
{
	sf::FloatRect playerRect(sf::Vector2f(player.getPosition().x + player.getBounds().left, player.getPosition().y + player.getBounds().top),
							 sf::Vector2f(player.getBounds().width, player.getBounds().height));

	sf::Vector2f platPos = getWorldPosition();

	// Is player in the same x position as the platform
	if (!(playerRect.left + playerRect.width > platPos.x&&
		playerRect.left < platPos.x + platformRect.width))
	{
		return false;
	}

	sf::Vector2f velocity = player.getVelocity();

	// Is player this frame above and the next will be below the platform
	if (playerRect.top + playerRect.height < platPos.y &&
		playerRect.top + playerRect.height + (velocity.y) * dtAsSeconds >= platPos.y)
	{
		player.setOnPlatform(this);
		return true;
	}

	return false;
}

int Platform::getHeight()
{
	return (int)platformRect.top;
}

int Platform::getPlatformNumber()
{
	return platformNumber;
}

void Platform::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(platformSprite, states);

	if (platformNumber % 10 == 0)
	{
		target.draw(numberRect, states);
		target.draw(floorNumberText, states);
	}

}
