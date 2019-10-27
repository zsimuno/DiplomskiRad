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


private:
	void								loadTextures();
	void								buildScene();


private:
	enum Layer
	{
		Background,
		Floors,
		Front,
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
	float								mWorldBorderWidth;
	sf::Sprite mBackground;
};

#endif // WORLD_HPP
