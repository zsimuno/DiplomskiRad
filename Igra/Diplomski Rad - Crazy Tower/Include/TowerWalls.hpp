#ifndef TOWERWALLS_HPP
#define TOWERWALLS_HPP

#include <SceneNode.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Player.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Text.hpp>

class Tower;
class TowerWalls : 
	public SceneNode
{
public:
	TowerWalls(float wallWidth, sf::View towerView, Tower& tower, Player& player, sf::Font& font);

	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void			updateCurrent(sf::Time dt) override;
private:
	Tower&					world;
	Player&					player;

	sf::RectangleShape		leftWall;
	sf::RectangleShape		rightWall;

	sf::Time				timer;
	sf::Text				timerText;
	sf::Text				comboText;
};
#endif // TOWERWALLS_HPP
