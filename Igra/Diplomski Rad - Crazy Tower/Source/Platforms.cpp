#include <Platforms.hpp>
#include <iostream>



Platforms::Platforms(sf::FloatRect& bounds, sf::Font& platformFont)
	: currentBounds(bounds)
	, font(platformFont)
{
	initialize();
}

bool Platforms::isOnPlatform(Player& player, float dtAsSeconds)
{

	for (Platform& p : platforms)
	{
		if (p.isOnPlatform(player, dtAsSeconds))
		{
			return true;
		}
	}
	return false;
}

void Platforms::updateCurrent(sf::Time dt)
{
	for (auto p = platforms.begin(); p != platforms.end(); p++)
	{
		if (p->getBounds().top > currentBounds.top + currentBounds.height)
		{
			p = platforms.erase(p);
		}
		else
		{
			break;
		}
	}

	if (platforms.back().getHeight() - platformDistance > currentBounds.top)
	{
		addNewPlatform();
	}

}

void Platforms::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Platform& p : platforms)
	{
		target.draw(p, states);
	}
}

void Platforms::initialize()
{
	platforms.clear();
	platforms.push_back(Platform(0, currentBounds, font));
	while (true)
	{
		if (platforms.back().getHeight() - Platform::platformHeight - 100 < currentBounds.top)
		{
			break;
		}
		addNewPlatform();
	}
}

void Platforms::addNewPlatform()
{
	auto p = platforms.back();
	platforms.push_back(Platform(p.getPlatformNumber() + 1, currentBounds, font, p.getHeight()));
}
