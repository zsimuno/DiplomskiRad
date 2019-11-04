#ifndef COMBOCOUNTER_HPP
#define COMBOCOUNTER_HPP

#include <SceneNode.hpp>
#include <Player.hpp>
#include <Utility.hpp>
#include <State.hpp>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>

class Tower;

class ComboCounter : public SceneNode
{
public:
	ComboCounter(State::Context gameContext, Tower& gameTower, Player& pl);

	virtual void			updateCurrent(sf::Time dt) override;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void					initialize();

private:
	Tower&					tower;
	Player&					player;

	bool					timerStarted;

	sf::Clock				comboTimer;
	sf::Text				comboText;

	sf::RectangleShape		comboBarBack;
	sf::RectangleShape		comboBarFront;

	static const int		comboBarWidth = 20;
	static const int		comboBarHeight = 150;

	int						comboNumber;
};

#endif // COMBOCOUNTER_HPP