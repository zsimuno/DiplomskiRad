#ifndef TOWERWALLS_HPP
#define TOWERWALLS_HPP

#include <SceneNode.hpp>
#include <Player.hpp>
#include <State.hpp>
#include <FloorSpeedTimer.hpp>
#include <ComboCounter.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>


class Tower;

class TowerWalls : public SceneNode
{
public:
							TowerWalls(float wallWidth, Tower& gameTower, Player& player, State::Context context);

	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	void					setGameSpeedTimer(bool state);
private:
	sf::Sprite				leftWall;
	sf::Sprite				rightWall;

	FloorSpeedTimer*		floorTimer;
	ComboCounter*			comboCounter;
};
#endif // TOWERWALLS_HPP
