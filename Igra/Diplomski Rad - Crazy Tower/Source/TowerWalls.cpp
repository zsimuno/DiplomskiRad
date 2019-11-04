#include <TowerWalls.hpp>
#include <Tower.hpp>
#include <Utility.hpp>

#include <SFML\Graphics\RenderTarget.hpp>

TowerWalls::TowerWalls(float wallWidth, Tower& gameTower, Player& player, State::Context context)
	: leftWall()
	, rightWall()
{
	sf::Texture& texture = context.textures->get(Textures::ID::Walls);
	texture.setRepeated(true);

	sf::IntRect textureRect(0, 0, (int)wallWidth, (int)context.window->getView().getSize().y);
	leftWall.setTexture(texture);
	leftWall.setTextureRect(textureRect);

	textureRect = sf::IntRect((int) context.window->getView().getSize().x - (int) wallWidth, 0, (int)wallWidth, (int)context.window->getView().getSize().y);
	rightWall.setTexture(texture);
	rightWall.setPosition(context.window->getView().getSize().x - wallWidth, 0);
	rightWall.setTextureRect(textureRect);

	// Create timer for floor speeds
	std::unique_ptr<FloorSpeedTimer> timer(new FloorSpeedTimer(context, gameTower, player));
	floorTimer = timer.get();
	timer->setPosition(30.f, 50.f);
	attachChild(std::move(timer));

	// Add combo counter and timer 
	std::unique_ptr<ComboCounter> combCnt(new ComboCounter(context, gameTower, player));
	comboCounter = combCnt.get();
	comboCounter->setPosition(40.f, 200.f);
	attachChild(std::move(combCnt));
	
}
void TowerWalls::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(leftWall, states);
	target.draw(rightWall, states);
}

void TowerWalls::setGameSpeedTimer(bool state)
{
	floorTimer->setGameSpeedTimer(state);
}
