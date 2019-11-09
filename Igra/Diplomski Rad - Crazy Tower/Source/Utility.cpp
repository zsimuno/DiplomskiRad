#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <Utility.hpp>

#include <cmath>


void Utility::centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}

void Utility::centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}

void Utility::centerOrigin(sf::RectangleShape& shape)
{
	sf::FloatRect bounds = shape.getLocalBounds();
	shape.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}

float Utility::mapValue(float value, float istart, float istop, float ostart, float ostop) {
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}
