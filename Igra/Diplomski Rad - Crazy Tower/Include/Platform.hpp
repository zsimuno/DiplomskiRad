#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <Player.hpp>

#include <SFML\Graphics\Rect.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\RenderStates.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

class Platform : public sf::Drawable
{
public:
	static const int	platformHeight = 50;
	Platform(int floorNumber, sf::Vector2i position = sf::Vector2i(0, 0));

	sf::IntRect			getBounds();
	bool				isOnPlatform( Player& player, float dtAsSeconds);
	int					getHeight();
private:

	sf::IntRect			platformRect;
	sf::RectangleShape	rect;

	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // PLATFORM_HPP