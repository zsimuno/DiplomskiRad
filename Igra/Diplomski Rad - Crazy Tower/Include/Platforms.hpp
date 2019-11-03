#ifndef PLATFORMS_HPP
#define PLATFORMS_HPP

#include <SceneNode.hpp>
#include <Player.hpp>
#include <Platform.hpp>

class Platforms : public SceneNode
{
public:
	static const int		platformDistance = Platform::platformHeight - 250;
	static int				startingPlatform;

	Platforms(sf::FloatRect& bounds, State::Context gameContext);

	bool					isOnPlatform(Player& player, float dtAsSeconds);
	virtual void			updateCurrent(sf::Time dt) override;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void					initialize();

private:
	std::vector<Platform>	platforms;

	sf::FloatRect&			currentBounds;

	State::Context			context;

	void					addNewPlatform();
};

#endif // PLATFORMS_HPP