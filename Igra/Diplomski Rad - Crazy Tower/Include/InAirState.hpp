#ifndef INAIRSTATE_HPP
#define INAIRSTATE_HPP

#include <PlayerState.hpp>

#include <SFML\System\Time.hpp>
#include <SFML\Window\Event.hpp>

class Player;

class InAirState : public PlayerState
{
public:
	InAirState(PlayerContext ctx);

	virtual void		update(sf::Time dt) override;
	virtual void		handleRealTimeEvent() override;

};

#endif // INAIRSTATE_HPP