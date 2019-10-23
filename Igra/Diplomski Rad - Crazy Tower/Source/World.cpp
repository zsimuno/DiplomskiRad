#include <World.hpp>
#include <PlayerData.hpp>
#include <iostream>

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBorderWidth(100.f)
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
	, mSpawnPosition(mWorldView.getSize().x / 2.f,  mWorldView.getSize().y - 100.f)
	, mScrollSpeed(-0.f)
	, mPlayer(nullptr)
{
	std::cout << std::to_string(mWorldBounds.left) <<  " x " << std::to_string(mWorldBorderWidth) << " wow";
	loadTextures();
	buildScene(); 
}

void World::update(sf::Time dt)
{
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	// Move the player sidewards (plane scouts follow the main aircraft)
	sf::Vector2f position = mPlayer->getPosition();
	sf::Vector2f velocity = mPlayer->getVelocity();

	// If player touches borders, flip its X velocity
	if (position.x <= mWorldBounds.left + 150.f
		|| position.x >= mWorldBounds.left + mWorldBounds.width - 150.f)
	{
		velocity.x = -velocity.x;
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
	std::cout << std::to_string(mWorldBounds.left) <<  " x " << std::to_string(mWorldBounds.top) << " wow";
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add player
	std::unique_ptr<Player> player(new Player(mTextures, &mScrollSpeed));
	mPlayer = player.get();
	mPlayer->setPosition(mSpawnPosition);
	mSceneLayers[Front]->attachChild(std::move(player));

}
