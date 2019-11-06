#ifndef FLOORSPEEDTIMER_HPP
#define FLOORSPEEDTIMER_HPP

#include <SceneNode.hpp>
#include <Player.hpp>
#include <State.hpp>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>

class Tower;

class FloorSpeedTimer : public SceneNode
{
public:
	FloorSpeedTimer(State::Context gameContext, Tower& gameTower, Player& player);

	virtual void			updateCurrent(sf::Time dt) override;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void					initialize();

	void					setGameSpeedTimer(bool state);

private:
	Tower&					tower;
	Player&					player;
	State::Context&				context;

	bool					timerStarted;

	sf::Clock				gameSpeedTimer;
	sf::Text				timerText;
};

#endif // FLOORSPEEDTIMER_HPP