#ifndef SPRITENODE_HPP
#define SPRITENODE_HPP

#include <SceneNode.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML\Graphics\RectangleShape.hpp>

class RectangleNode : public SceneNode
{
public:
						RectangleNode(float x, float y, float width, float height);

private:
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::RectangleShape	rect;
};

#endif // SPRITENODE_HPP