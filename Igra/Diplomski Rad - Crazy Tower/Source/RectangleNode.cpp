#include <RectangleNode.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML\Graphics\Sprite.hpp>



RectangleNode::RectangleNode(float x, float y, float width, float height)
	: rect(sf::Vector2f(width, height))
{
	rect.setPosition(x, y);
	rect.setFillColor(sf::Color(105, 105, 105));
}

void RectangleNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.draw(rect, states);
}