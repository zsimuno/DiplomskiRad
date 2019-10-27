#include <Platform.hpp>
#include <iostream>


Platform::Platform(int floorNumber, sf::Vector2i position)
	: platformRect(position, sf::Vector2i(1000, 30)),
	rect()
{
	int heightLower = 30;
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

	rect.setSize(sf::Vector2f(platformRect.width, platformRect.height));
	rect.setPosition(sf::Vector2f(platformRect.left, platformRect.top));

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
	float ss = player.getWorldScrollSpeed();
	
	// Is player this frame above and the next will be below the platform
	if (playerRect.top + playerRect.height < platformRect.top &&
		playerRect.top + playerRect.height + (velocity.y + ss) * dtAsSeconds >= platformRect.top)
	{
		player.setOnPlatform(this);
		return true;
	}

	return false;
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rect, states);
}
