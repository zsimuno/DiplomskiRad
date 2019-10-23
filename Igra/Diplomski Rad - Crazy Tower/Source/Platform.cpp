#include "..\Include\Platform.hpp"

Platform::Platform(int floorNumber)
	: platformRect(0, 0, 100, 30)
{
	int heightLower = 30;
	if (floorNumber % 50 != 0)
	{
		platformRect.left = 100;
	}

	if (floorNumber < 100) {
		
	} else if (floorNumber < 200) {

	}
	else if (floorNumber < 300) {

	}
	else if (floorNumber < 400) {

	} else 
	{
		platformRect.width = 200;
	}
}

sf::IntRect Platform::getBounds()
{
	return platformRect;
}
