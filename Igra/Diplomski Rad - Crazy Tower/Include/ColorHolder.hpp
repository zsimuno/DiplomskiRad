#ifndef COLORHOLDER_HPP
#define COLORHOLDER_HPP

#include <ResourceIdentifiers.hpp>

#include <SFML/Graphics/Color.hpp>

#include <map>
#include <memory>

class ColorHolder
{
public:
	sf::Color&										get(Colors::ID id);
	const sf::Color&								get(Colors::ID id) const;
	void											set(Colors::ID id, sf::Color color);
private:
	std::map<Colors::ID, sf::Color> colorsMap;
};

#endif // COLORHOLDER_HPP
