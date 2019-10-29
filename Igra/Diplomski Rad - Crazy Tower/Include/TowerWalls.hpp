#ifndef TOWERWALLS_HPP
#define TOWERWALLS_HPP

#include <SceneNode.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Player.hpp>

class World;
class TowerWalls : 
	public SceneNode
{
public:
	TowerWalls(float wallWidth, float wallHeight, World& world, Player& player);
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void			updateCurrent(sf::Time dt) override;
private:
	World& world;
	Player& player;

	sf::RectangleShape		leftWall;
	sf::RectangleShape		rightWall;
};
#endif // TOWERWALLS_HPP
