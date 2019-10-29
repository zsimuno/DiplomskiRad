#include <World.hpp>
#include <PlayerData.hpp>
#include <iostream>
#include <TowerWalls.hpp>

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
	, mSpawnPosition(mWorldView.getSize().x / 2.f,  mWorldView.getSize().y - 140.f)
	, mScrollSpeed(-10.f)
	, mPlayer(nullptr)
	, mWorldWallWidth(100.f)
{
	loadTextures();
	buildScene(); 
}

void World::update(sf::Time dt)
{
	mWorldView.move(0.f, ScrollSpeed() * dt.asSeconds());
	mWalls->move(0.f, ScrollSpeed() * dt.asSeconds());

	sf::Vector2f position = mPlayer->getPosition();
	sf::FloatRect bounds = mPlayer->getBounds();
	sf::Vector2f velocity = mPlayer->getVelocity();

	// If player touches borders, flip its X velocity
	if (position.x - bounds.width/2 <= mWorldBounds.left + mWorldWallWidth ||
		position.x + bounds.width/2 >= mWorldBounds.left + mWorldBounds.width - mWorldWallWidth)
	{
		velocity.x = -2*velocity.x;
		mPlayer->setVelocity(velocity);
	}

	// Apply movements
	mSceneGraph.update(dt);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

float World::ScrollSpeed()
{
	return mScrollSpeed; 
}

void World::incrementScrollSpeed()
{
	mScrollSpeed++;
}

void World::move(sf::Vector2f v)
{
	mWorldView.move(v);
}


void World::loadTextures()
{
	mTextures.load(Textures::ID::Character, "Media/Textures/character.png");
	mTextures.load(Textures::ID::Tower, "Media/Textures/background.png");
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::ID::Tower);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect, mWorldView));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Create platforms
	std::unique_ptr<Platforms> platforms(new Platforms());
	Platforms* mPlatforms = platforms.get();
	mSceneLayers[Floors]->attachChild(std::move(platforms));

	// Add player
	std::unique_ptr<Player> player(new Player(mTextures, mScrollSpeed, *mPlatforms));
	mPlayer = player.get();
	mPlayer->setPosition(mSpawnPosition);
	mSceneLayers[Front]->attachChild(std::move(player));

	// Add tower walls
	std::unique_ptr<TowerWalls> towerWalls(new TowerWalls(mWorldWallWidth, mWorldView.getSize().y, *this, *mPlayer));
	mWalls = towerWalls.get();
	mSceneLayers[Walls]->attachChild(std::move(towerWalls));

}
