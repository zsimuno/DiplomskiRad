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

	bool					isPlayerOnPlatform(Player& player, float dtAsSeconds);
	virtual void			updateCurrent(sf::Time dt) override;
	void					initialize();

private:
	void					addNewPlatform();

	sf::FloatRect&			currentBounds;

	State::Context			context;
};

#endif // PLATFORMS_HPP