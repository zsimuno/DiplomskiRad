#include <SpriteNode.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML\Graphics\Sprite.hpp>



SpriteNode::SpriteNode(const sf::Texture& texture, sf::View& worldView)
	: mSprite(texture),
	mWorldView(worldView)
{
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect, sf::View& worldView)
	: mSprite(texture, textureRect),
	mWorldView(worldView)
{
}

void SpriteNode::updateCurrent(sf::Time dt)
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.draw(mSprite, states);
}