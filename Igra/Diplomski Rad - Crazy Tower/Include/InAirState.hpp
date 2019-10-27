#ifndef INAIRSTATE_HPP
#define INAIRSTATE_HPP

#include <PlayerState.hpp>

#include <SFML\System\Time.hpp>
#include <SFML\Window\Event.hpp>
#include <Player.hpp>

class InAirState : public PlayerState
{
public:
	InAirState(Player& pl);

	virtual void		draw() override;
	virtual void		update(sf::Time dt) override;
	virtual void		handleEvent(const sf::Event& event) override;

private:
	Player& player;
};

#endif // INAIRSTATE_HPP