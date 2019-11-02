#include <Platform.hpp>
#include <iostream>

#include <Utility.hpp>
#include <SFML/Graphics/Font.hpp>


Platform::Platform(int floorNumber, sf::FloatRect towerBounds, sf::Font& font, int previousPlatform)
	: platformRect()
	, platformNumber(floorNumber)
	, rect()
	, floorNumberText(std::to_string(floorNumber), font)
{
	platformRect.top = previousPlatform - Platform::platformHeight - 100;
	platformRect.height = platformHeight;
	
	if (floorNumber < 100)
	{
		rect.setFillColor(sf::Color::Blue);
		platformRect.width = minPlatformWidth + rand() % (int)(towerBounds.width*0.5);
	}
	else if (floorNumber < 200)
	{
		rect.setFillColor(sf::Color::Red);
		platformRect.width = minPlatformWidth + rand() % (int)(towerBounds.width * 0.4);
	}
	else if (floorNumber < 300)
	{
		rect.setFillColor(sf::Color::Green);
		platformRect.width = minPlatformWidth + rand() % (int)(towerBounds.width * 0.3);
	}
	else if (floorNumber < 400)
	{
		rect.setFillColor(sf::Color::Yellow);
		platformRect.width = minPlatformWidth + rand() % (int)(towerBounds.width * 0.2);
	}
	else
	{
		rect.setFillColor(sf::Color::Black);
		platformRect.width = minPlatformWidth;
	}

	platformRect.left = towerBounds.left + rand() % (int)(towerBounds.width - platformRect.width);

	if (floorNumber % 50 == 0)
	{
		platformRect.left = towerBounds.left;
		platformRect.width = towerBounds.width;

		if (platformNumber == 0)
		{
			platformRect.top = towerBounds.top + towerBounds.height - Platform::platformHeight;
		}

	}

	rect.setSize(sf::Vector2f(platformRect.width, platformRect.height));
	rect.setPosition(sf::Vector2f(platformRect.left, platformRect.top));
	rect.setOutlineThickness(-5);
	rect.setOutlineColor(sf::Color::Cyan);

	floorNumberText.setCharacterSize(14);
	floorNumberText.setFillColor(sf::Color::Black);
	Utility::centerOrigin(floorNumberText);
	floorNumberText.setPosition(platformRect.left + platformRect.width / 2, platformRect.top + platformRect.height - 15);

	numberRect.setSize(sf::Vector2f(50, 30));
	Utility::centerOrigin(numberRect);
	numberRect.setPosition(platformRect.left + platformRect.width / 2, platformRect.top + platformRect.height - 15);
	numberRect.setFillColor(sf::Color::White);
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


	// Is player in the same x position as the platform
	if (!(playerRect.left + playerRect.width > platformRect.left&&
		playerRect.left < platformRect.left + platformRect.width))
	{
		return false;
	}

	sf::Vector2f velocity = player.getVelocity();

	// Is player this frame above and the next will be below the platform
	if (playerRect.top + playerRect.height < platformRect.top &&
		playerRect.top + playerRect.height + (velocity.y) * dtAsSeconds >= platformRect.top)
	{
		player.setOnPlatform(this);
		return true;
	}

	return false;
}

int Platform::getHeight()
{
	return platformRect.top;
}

int Platform::getPlatformNumber()
{
	return platformNumber;
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect, states);
	target.draw(numberRect, states);
	target.draw(floorNumberText, states);
}
