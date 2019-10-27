#ifndef PLAYERSTATE_HPP
#define PLAYERSTATE_HPP

#include <SFML\System\Time.hpp>
#include <SFML\Window\Event.hpp>
#include <PlayerData.hpp>

class PlayerState
{
public:
	struct PlayerContext
	{
		PlayerContext(
			PlayerInfo& data,
			Player& player);
		PlayerInfo* data;
		Player* player;
	};

	PlayerState( PlayerContext ctx);

	virtual void		update(sf::Time dt) = 0;
	virtual void		handleRealTimeEvent() = 0;

protected:
	PlayerContext		context;
};

#endif // PLAYERSTATE_HPP
