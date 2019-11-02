#ifndef PLATFORMS_HPP
#define PLATFORMS_HPP

#include <SceneNode.hpp>
#include <Player.hpp>
#include <Platform.hpp>

class Player;
class Platforms : public SceneNode
{
public:
	static const int		platformDistance = Platform::platformHeight - 300;

	Platforms(sf::FloatRect& bounds, sf::Font& platformFont);

	bool					isOnPlatform(Player& player, float dtAsSeconds);
	virtual void			updateCurrent(sf::Time dt) override;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void					initialize();

private:
	const static int		maxNumberOfPlatforms = 7;

	std::vector<Platform>	platforms;

	sf::FloatRect&			currentBounds;
	sf::Font&				font;

	void					addNewPlatform();
};

#endif // PLATFORMS_HPP