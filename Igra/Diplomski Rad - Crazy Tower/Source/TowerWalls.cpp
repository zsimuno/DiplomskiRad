#include <TowerWalls.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

TowerWalls::TowerWalls(float wallWidth, float wallHeight, World& world, Player& player)
	:world(world),
	player(player),
	leftWall(sf::Vector2f(wallWidth, wallHeight)),
	rightWall(sf::Vector2f(wallWidth, wallHeight))
{
	leftWall.setPosition(0, 0);
	rightWall.setPosition(1024 - wallWidth, 0);
	leftWall.setFillColor(sf::Color::Blue);
	rightWall.setFillColor(sf::Color::Blue);
}
void TowerWalls::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(leftWall, states);
	target.draw(rightWall, states);
}

void TowerWalls::updateCurrent(sf::Time dt)
{
}
