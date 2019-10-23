#include <SFML/Graphics/Sprite.hpp>
#include <Utility.hpp>

#include <cmath>

void Utility::centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}