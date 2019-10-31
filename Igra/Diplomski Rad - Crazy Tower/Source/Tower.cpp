#include <Tower.hpp>
#include <PlayerData.hpp>
#include <iostream>
#include <TowerWalls.hpp>

Tower::Tower(sf::RenderWindow& window)
	: mWindow(window)
	, worldView(window.getDefaultView())
	, textures()
	, sceneGraph()
	, sceneLayers()
	, worldBounds(0.f, 0.f, worldView.getSize().x, worldView.getSize().y)
	, spawnPosition(worldView.getSize().x / 2.f,  worldView.getSize().y - 140.f)
	, scrollSpeed(-10.f)
	, player(nullptr)
	, towerWallWidth(100.f)
{
	loadTextures();
	buildScene(); 
}

void Tower::update(sf::Time dt)
{
	worldView.move(0.f, ScrollSpeed() * dt.asSeconds());
	walls->move(0.f, ScrollSpeed() * dt.asSeconds());

	sf::Vector2f position = player->getPosition();
	sf::FloatRect bounds = player->getBounds();
	sf::Vector2f velocity = player->getVelocity();

	// If player touches walls, flip him and multiply the velocity
	if (position.x - bounds.width/2 <= worldBounds.left + towerWallWidth ||
		position.x + bounds.width/2 >= worldBounds.left + worldBounds.width - towerWallWidth)
	{
		velocity.x = -2*velocity.x;
		player->setVelocity(velocity);
	}

	sceneGraph.update(dt);
}

void Tower::draw()
{
	mWindow.setView(worldView);
	mWindow.draw(sceneGraph);
}

float Tower::ScrollSpeed()
{
	return scrollSpeed; 
}

void Tower::incrementScrollSpeed()
{
	scrollSpeed++;
}

void Tower::move(sf::Vector2f v)
{
	worldView.move(v);
}


void Tower::loadTextures()
{
	textures.load(Textures::ID::Character, "Media/Textures/character.png");
	textures.load(Textures::ID::Tower, "Media/Textures/background.png");
}

void Tower::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		sceneLayers[i] = layer.get();

		sceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = textures.get(Textures::ID::Tower);
	sf::IntRect textureRect(worldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect, worldView));
	backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
	sceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Create platforms
	std::unique_ptr<Platforms> platforms(new Platforms());
	Platforms* mPlatforms = platforms.get();
	sceneLayers[Floors]->attachChild(std::move(platforms));

	// Add player
	std::unique_ptr<Player> gamePlayer(new Player(textures, *mPlatforms));
	player = gamePlayer.get();
	player->setPosition(spawnPosition);
	sceneLayers[Front]->attachChild(std::move(gamePlayer));

	// Add tower walls
	std::unique_ptr<TowerWalls> towerWalls(new TowerWalls(towerWallWidth, worldView.getSize().y, *this, *player));
	walls = towerWalls.get();
	sceneLayers[Walls]->attachChild(std::move(towerWalls));

}
