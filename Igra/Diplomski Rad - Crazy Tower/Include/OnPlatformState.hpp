#ifndef ONPLATFORMSTATE_HPP
#define ONPLATFORMSTATE_HPP

#include <PlayerState.hpp>

#include <SFML\System\Time.hpp>
#include <SFML\Window\Event.hpp>

class Platform;
class Player;

class OnPlatformState : public PlayerState
{
public:
	OnPlatformState(PlayerContext ctx);

	virtual void		update(sf::Time dt) override;
	virtual void		handleRealTimeEvent() override;

};

#endif // ONPLATFORMSTATE_HPP
