#include <Platforms.hpp>
#include <iostream>



Platforms::Platforms() 
{
	for (int i = 1; i <= maxNumberOfPlatforms; ++i)
	{
		platforms.push_back(Platform(i, sf::Vector2i(100, (maxNumberOfPlatforms - i + 1) * 100)));
	}
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

void Platforms::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Platform& p : platforms)
	{
		target.draw(p, states);
	}
}
