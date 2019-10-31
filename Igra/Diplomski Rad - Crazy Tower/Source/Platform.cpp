#include <Platform.hpp>
#include <iostream>


Platform::Platform(int floorNumber, sf::Vector2i position)
	: platformRect(position, sf::Vector2i(1000, platformHeight)),
	rect()
{
	if (floorNumber % 50 != 0)
	{
		platformRect.left = 100;
		platformRect.width = 500;
	}

	if (floorNumber < 100) {
		rect.setFillColor(sf::Color::Blue);
	} else if (floorNumber < 200) {
		rect.setFillColor(sf::Color::Red);
	}
	else if (floorNumber < 300) {
		rect.setFillColor(sf::Color::Green);
	}
	else if (floorNumber < 400) {
		rect.setFillColor(sf::Color::Yellow);
	} else 
	{
		rect.setFillColor(sf::Color::Black);
		platformRect.width = 200;
	}

	rect.setSize(sf::Vector2f((float)platformRect.width, (float)platformRect.height));
	rect.setPosition(sf::Vector2f((float)platformRect.left, (float)platformRect.top));
	rect.setOutlineThickness(5);
	rect.setOutlineColor(sf::Color::Cyan);
	
}

sf::IntRect Platform::getBounds()
{
	return platformRect;
}

bool Platform::isOnPlatform(Player& player, float dtAsSeconds)
{
	sf::FloatRect playerRect(sf::Vector2f(player.getPosition().x + player.getBounds().left, player.getPosition().y + player.getBounds().top),
							 sf::Vector2f(player.getBounds().width, player.getBounds().height));
	

	// Is player in the same x position as the platform
	if (!(playerRect.left + playerRect.width > platformRect.left &&
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

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect, states);
}
