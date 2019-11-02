#include <TowerWalls.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

TowerWalls::TowerWalls(float wallWidth, sf::View towerView, Tower& world, Player& player, sf::Font& font)
	:world(world)
	, player(player)
	, leftWall(sf::Vector2f(wallWidth, towerView.getSize().y))
	, rightWall(sf::Vector2f(wallWidth, towerView.getSize().y))
	, timerText("30", font)
	, comboText("0", font)
{
	leftWall.setPosition(0, 0);
	rightWall.setPosition(towerView.getSize().x - wallWidth, 0);
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
	//comboText.setString(player.getCombo());
}
