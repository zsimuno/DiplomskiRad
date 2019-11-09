#include <Tower.hpp>
#include <PlayerData.hpp>
#include <TowerWalls.hpp>
#include <State.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

Tower::Tower(sf::RenderWindow& window, State::Context gameContext)
	: window(window)
	, context(gameContext)
	, worldView(window.getDefaultView())
	, sceneGraph()
	, sceneLayers()
	, towerWallWidth(worldView.getSize().x / 6)
	, scrollSpeed(0.f)
	, player(nullptr)
	, gameOver(false)
	, comboText("", context.fonts->get(Fonts::ID::Secondary))
	, comboClock()
{
	comboText.setFillColor(sf::Color::White);
	comboText.setOutlineColor(sf::Color::Black);
	comboText.setOutlineThickness(2);
	comboText.setCharacterSize(100);
	comboText.setPosition(worldView.getSize().x / 2, worldView.getSize().y / 2);

	context.soundPlayer->play(Sounds::ID::Hi);

	insideTowerBounds = sf::FloatRect(towerWallWidth, 0.f, worldView.getSize().x - 2 * towerWallWidth, worldView.getSize().y);
	buildScene(); 
}

void Tower::update(sf::Time dt)
{
	moveWorld(sf::Vector2f(0.f, ScrollSpeed() * dt.asSeconds()));

	sf::Vector2f position = player->getPosition();
	sf::FloatRect bounds = player->getBounds();

	// If player touches walls, flip him and multiply the velocity
	if (position.x - bounds.width/2 <= insideTowerBounds.left ||
		position.x + bounds.width/2 >= insideTowerBounds.left + insideTowerBounds.width )
	{
		sf::Vector2f velocity = player->getVelocity();
		velocity.x = -1.5f*velocity.x;
		player->setVelocity(velocity);
	}

	// If player out of bounds then game over
	if (position.y - bounds.height / 2 >= insideTowerBounds.top + insideTowerBounds.height)
	{
		gameOver = true;
		context.soundPlayer->play(Sounds::ID::Falling);

		context.leaderboards->checkScore(player->getHighestPlatform(), player->getHighestCombo());
	}

	// Move the screen with the player. Player must always be on screen
	sf::Vector2f velocity = player->getVelocity();
	if (position.y < insideTowerBounds.top + insideTowerBounds.height / 4 && velocity.y < 0)
	{
		moveWorld(sf::Vector2f(0.f, velocity.y * dt.asSeconds() * Utility::mapValue(position.y, insideTowerBounds.height / 4, insideTowerBounds.top, 0, 1)));
	}


	// Start the game when player jumps more than 3 platforms
	if (scrollSpeed == 0.f && player->getPlatformNumber() > Platforms::startingPlatform + 3)
	{
		incrementScrollSpeed();
		walls->setGameSpeedTimer(true);
	}

	sceneGraph.update(dt);

	context.soundPlayer->removeStoppedSounds();
}

void Tower::moveWorld(sf::Vector2f moveDistance)
{
	worldView.move(moveDistance);
	walls->move(moveDistance);
	insideTowerBounds.top += moveDistance.y;
	rectangle->move(moveDistance);
	comboText.move(moveDistance);


}



void Tower::draw()
{
	window.setView(worldView);
	window.draw(sceneGraph);

	if (comboClock.getElapsedTime().asSeconds() < 2.f)
	{
		window.draw(comboText);
	}
}

float Tower::ScrollSpeed()
{
	return scrollSpeed; 
}

void Tower::incrementScrollSpeed()
{
	scrollSpeed += Tower::ScrollSpeedIncrement;
}

void Tower::move(sf::Vector2f v)
{
	worldView.move(v);
}


bool Tower::GameOver() const
{
	return gameOver;
}


void Tower::buildScene()
{
	// Initialize layers
	for (int i = 0; i < LayerCount; ++i)
	{
		SceneNode::NodePointer layer(new SceneNode());
		sceneLayers[i] = layer.get();
		sceneGraph.attachChild(std::move(layer));
	}


	// Add the background 
	std::unique_ptr<RectangleNode> rectangleNode(new RectangleNode(insideTowerBounds));
	rectangle = rectangleNode.get();
	sceneLayers[Background]->attachChild(std::move(rectangleNode));

	// Create platforms
	std::unique_ptr<Platforms> towerPlatforms(new Platforms(insideTowerBounds, context));
	platforms = towerPlatforms.get();
	platforms->setPosition(insideTowerBounds.left, insideTowerBounds.top);
	sceneLayers[Floors]->attachChild(std::move(towerPlatforms));

	// Add player
	std::unique_ptr<Player> gamePlayer(new Player(context, *platforms, *this));
	player = gamePlayer.get();
	spawnPosition = sf::Vector2f(worldView.getSize().x / 2.f, worldView.getSize().y - Platform::platformHeight - player->getBounds().height / 2);
	player->setPosition(spawnPosition);
	sceneLayers[Front]->attachChild(std::move(gamePlayer));

	// Add tower walls
	std::unique_ptr<TowerWalls> towerWalls(new TowerWalls(towerWallWidth, *this, *player, context));
	walls = towerWalls.get();
	sceneLayers[Walls]->attachChild(std::move(towerWalls));

}

void Tower::initialize()
{
	worldView = window.getDefaultView();
	insideTowerBounds = sf::FloatRect(towerWallWidth, 0.f, worldView.getSize().x - 2* towerWallWidth, worldView.getSize().y);
	scrollSpeed = 0.f;
	player->setPosition(spawnPosition);
	player->initialize();
	walls->setPosition(0.f, 0.f);
	walls->setGameSpeedTimer(false);
	rectangle->setPosition(insideTowerBounds.left, insideTowerBounds.top);
	platforms->initialize();
	comboText.setPosition(worldView.getSize().x / 2, worldView.getSize().y / 2);
	gameOver = false;
}

void Tower::drawComboText(float floors)
{
	if (floors < 4)
	{
		return;
	}
	comboClock.restart();
	if (floors > 4 && floors < 7) 
	{
		comboText.setString("Good!");
		context.soundPlayer->play(Sounds::ID::Good);
	}
	else if (floors < 15)
	{
		comboText.setString("Sweet!");
		context.soundPlayer->play(Sounds::ID::Sweet);
	}
	else if (floors < 25)
	{
		comboText.setString("Great!");
		context.soundPlayer->play(Sounds::ID::Great);
	}
	else if (floors < 35)
	{
		comboText.setString("Super!");
		context.soundPlayer->play(Sounds::ID::Super);
	}
	else if (floors < 50)
	{
		comboText.setString("Wow!");
		context.soundPlayer->play(Sounds::ID::Wow);
	}
	else if (floors < 70)
	{
		comboText.setString("Amazing!");
		context.soundPlayer->play(Sounds::ID::Amazing);
	}
	else if (floors < 100)
	{
		comboText.setString("Extreme!");
		context.soundPlayer->play(Sounds::ID::Extreme);
	}
	else if (floors < 140)
	{
		comboText.setString("Fantastic!");
		context.soundPlayer->play(Sounds::ID::Fantastic);
	}
	else if (floors < 200)
	{
		comboText.setString("Splendid!");
		context.soundPlayer->play(Sounds::ID::Splendid);
	}
	else 
	{
		comboText.setString("No Way!");
		context.soundPlayer->play(Sounds::ID::NoWay);
	}
}
