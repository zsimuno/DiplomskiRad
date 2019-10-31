#ifndef TOWERWALLS_HPP
#define TOWERWALLS_HPP

#include <SceneNode.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Player.hpp>

class Tower;
class TowerWalls : 
	public SceneNode
{
public:
	TowerWalls(float wallWidth, float wallHeight, Tower& world, Player& player);
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void			updateCurrent(sf::Time dt) override;
private:
	Tower& world;
	Player& player;

	sf::RectangleShape		leftWall;
	sf::RectangleShape		rightWall;
};
#endif // TOWERWALLS_HPP
