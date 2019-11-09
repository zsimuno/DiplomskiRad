#include <RectangleNode.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>



RectangleNode::RectangleNode(sf::FloatRect bounds)
	: rect(sf::Vector2f(bounds.width, bounds.height))
{
	this->setPosition(bounds.left, bounds.top);
	rect.setFillColor(sf::Color(0xB3E5FCFF));
}

void RectangleNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.draw(rect, states);
}