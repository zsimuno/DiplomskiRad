#include <ColorHolder.hpp>

#include <assert.h>


sf::Color& ColorHolder::get(Colors::ID id)
{
	auto found = colorsMap.find(id);
	assert(found != colorsMap.end());

	return found->second;
}

const sf::Color& ColorHolder::get(Colors::ID id) const
{
	auto found = colorsMap.find(id);
	assert(found != colorsMap.end());

	return found->second;
}

void ColorHolder::set(Colors::ID id, sf::Color color)
{
	auto inserted = colorsMap.insert(std::make_pair(id, color));
	assert(inserted.second);
}
