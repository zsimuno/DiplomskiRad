#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class Utility
{
public:
	static void			centerOrigin(sf::Sprite& sprite);
	static void			centerOrigin(sf::Text& text);
	static void			centerOrigin(sf::RectangleShape& shape);
	static float		mapValue(float value, float istart, float istop, float ostart, float ostop);
};

#endif // UTILITY_HPP