#ifndef WORLD_HPP
#define WORLD_HPP

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <SceneNode.hpp>
#include <RectangleNode.hpp>
#include <Player.hpp>
#include <Platforms.hpp>
#include <TowerWalls.hpp>
#include <State.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML\System\Time.hpp>

#include <array>



namespace sf
{
	class RenderWindow;
}

class Tower : private sf::NonCopyable
{
public:
	explicit							Tower(sf::RenderWindow& window, State::Context& gameContext);
	void								update(sf::Time dt);
	void								draw();
	float								ScrollSpeed();
	void								incrementScrollSpeed();
	void								move(sf::Vector2f v);
	bool								GameOver() const;
	void								initialize();

private:
	void								buildScene();
	


private:
	enum Layers
	{
		Background,
		Floors,
		Front,
		Walls,
		LayerCount
	};


private:
	sf::RenderWindow&					window;
	sf::View							worldView;
	State::Context&						context;

	SceneNode							sceneGraph;
	std::array<SceneNode*, LayerCount>	sceneLayers;

	sf::FloatRect						insideTowerBounds;
	sf::Vector2f						spawnPosition;
	sf::Sprite							background;
	
	Player*								player;
	TowerWalls*							walls;
	Platforms*							platforms;
	RectangleNode*						rectangle;

	float								towerWallWidth;
	float								scrollSpeed;
	bool								gameOver;
};

#endif // WORLD_HPP
