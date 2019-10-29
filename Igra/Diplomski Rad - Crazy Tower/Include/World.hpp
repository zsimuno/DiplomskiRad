#ifndef WORLD_HPP
#define WORLD_HPP

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <SceneNode.hpp>
#include <SpriteNode.hpp>
#include <Player.hpp>
#include <Platforms.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <SFML\System\Time.hpp>
#include "TowerWalls.hpp"

namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
public:
	explicit							World(sf::RenderWindow& window);
	void								update(sf::Time dt);
	void								draw();
	float								ScrollSpeed();
	void								incrementScrollSpeed();
	void								move(sf::Vector2f v);
private:
	void								loadTextures();
	void								buildScene();


private:
	enum Layer
	{
		Background,
		Floors,
		Front,
		Walls,
		LayerCount
	};


private:
	sf::RenderWindow& mWindow;
	sf::View							mWorldView;
	TextureHolder						mTextures;

	SceneNode							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;

	sf::FloatRect						mWorldBounds;
	sf::Vector2f						mSpawnPosition;
	float								mScrollSpeed;
	Player*								mPlayer;
	TowerWalls*							mWalls;
	float								mWorldWallWidth;
	sf::Sprite mBackground;
};

#endif // WORLD_HPP
