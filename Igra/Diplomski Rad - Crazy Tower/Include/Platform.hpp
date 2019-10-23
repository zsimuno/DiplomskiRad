#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <SFML\Graphics\Rect.hpp>

class Platform
{
public:
	Platform(int floorNumber);

	sf::IntRect getBounds();

private:

	sf::IntRect platformRect;
};

#endif // PLATFORM_HPP