#include <SFML/Graphics/Sprite.hpp>
#include <Utility.hpp>

#include <cmath>

void Utility::centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}