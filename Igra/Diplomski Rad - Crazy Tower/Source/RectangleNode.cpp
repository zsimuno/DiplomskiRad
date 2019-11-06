#include <RectangleNode.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>



RectangleNode::RectangleNode(float x, float y, float width, float height)
	: rect(sf::Vector2f(width, height))
{
	this->setPosition(x, y);
	rect.setFillColor(sf::Color(0xB3E5FCFF));
}

void RectangleNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.draw(rect, states);
}