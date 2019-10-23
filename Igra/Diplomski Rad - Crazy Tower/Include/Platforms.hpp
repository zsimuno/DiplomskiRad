#ifndef PLATFORMS_HPP
#define PLATFORMS_HPP

#include <SceneNode.hpp>
#include <Platform.hpp>
#include <World.hpp>
class Platforms :
	public SceneNode
{
public:
	Platforms();

	bool isOnPlatform(Player player);
	
private:
	const static int maxNumberOfPlatforms = 7;
	//Platform platforms[maxNumberOfPlatforms];
};

#endif // PLATFORMS_HPP