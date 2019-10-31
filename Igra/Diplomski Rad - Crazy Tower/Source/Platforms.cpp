#include <Platforms.hpp>
#include <iostream>



Platforms::Platforms() 
{
	platforms.push_back(Platform(1, sf::Vector2i(0, 768 + Platform::platformHeight)));
	for (int i = 2; i <= maxNumberOfPlatforms; ++i)
	{
		platforms.push_back(Platform(i, sf::Vector2i(rand() % 500 + 400, platforms.back().getHeight() - Platform::platformHeight - 200)));
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
