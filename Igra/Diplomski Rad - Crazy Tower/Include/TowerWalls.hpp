#ifndef TOWERWALLS_HPP
#define TOWERWALLS_HPP

#include <SceneNode.hpp>
#include <Player.hpp>
#include <State.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

class Tower;
class TowerWalls : 
	public SceneNode
{
public:
	TowerWalls(float wallWidth, Tower& gameTower, Player& player, State::Context context);

	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void			updateCurrent(sf::Time dt) override;

	void					setGameSpeedTimer(bool state);
private:
	Tower&					tower;
	Player&					player;

	sf::Sprite				leftWall;
	sf::Sprite				rightWall;

	bool					timerStarted;

	sf::Clock				comboTimer;
	sf::Clock				gameSpeedTimer;
	sf::Text				timerText;
	sf::Text				comboText;

	sf::RectangleShape		comboBarBack;
	sf::RectangleShape		comboBarFront;

	sf::Vector2f			barPosition;

	static const int		comboBarWidth = 20;
	static const int		comboBarHeight = 150;

	int						comboNumber;
};
#endif // TOWERWALLS_HPP
