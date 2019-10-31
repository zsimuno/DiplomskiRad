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

class Tower : private sf::NonCopyable
{
public:
	explicit							Tower(sf::RenderWindow& window);
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
	sf::View							worldView;
	TextureHolder						textures;

	SceneNode							sceneGraph;
	std::array<SceneNode*, LayerCount>	sceneLayers;

	sf::FloatRect						worldBounds;
	sf::Vector2f						spawnPosition;
	float								scrollSpeed;
	Player*								player;
	TowerWalls*							walls;
	float								towerWallWidth;
	sf::Sprite mBackground;
};

#endif // WORLD_HPP
