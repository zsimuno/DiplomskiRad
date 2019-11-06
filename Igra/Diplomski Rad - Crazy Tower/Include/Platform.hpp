#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <Player.hpp>


#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>



class Platform : public SceneNode
{
public:
	static const int	platformHeight = 50;
	float				minPlatformWidth = 200;

	Platform(int floorNumber, sf::FloatRect towerBounds, State::Context gameContext, int previousPlatform = 0);

	sf::FloatRect		getBounds();
	bool				isOnPlatform(Player& player, float dtAsSeconds);
	int					getHeight();
	int					getPlatformNumber();
private:

	sf::FloatRect		platformRect;
	sf::Sprite			platformSprite;
	sf::RectangleShape	numberRect;
	sf::Text			floorNumberText;
	int					platformNumber;

	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // PLATFORM_HPP