#ifndef PLATFORMS_HPP
#define PLATFORMS_HPP

#include <SceneNode.hpp>
#include <Player.hpp>
#include <Platform.hpp>

class Player;
class Platforms :
	public SceneNode
{
public:
	Platforms();

	bool					isOnPlatform(Player& player, float dtAsSeconds);
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	
private:
	const static int maxNumberOfPlatforms = 7;
	std::vector<Platform> platforms;
};

#endif // PLATFORMS_HPP