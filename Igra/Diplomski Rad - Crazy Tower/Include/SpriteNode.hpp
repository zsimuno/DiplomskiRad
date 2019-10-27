#ifndef SPRITENODE_HPP
#define SPRITENODE_HPP

#include <SceneNode.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML/Graphics/View.hpp>

class SpriteNode : public SceneNode
{
public:
	explicit			SpriteNode(const sf::Texture& texture, sf::View& worldView);
						SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect, sf::View& worldView);

	virtual void		updateCurrent(sf::Time dt) override;
private:
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite			mSprite;
	sf::View&			mWorldView;
};

#endif // SPRITENODE_HPP