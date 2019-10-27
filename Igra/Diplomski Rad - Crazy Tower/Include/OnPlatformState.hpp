#ifndef ONPLATFORMSTATE_HPP
#define ONPLATFORMSTATE_HPP

#include <PlayerState.hpp>

#include <SFML\System\Time.hpp>
#include <SFML\Window\Event.hpp>
#include <Player.hpp>

class OnPlatformState : public PlayerState
{
public:
	OnPlatformState(Player& player);

	virtual void		draw() override;
	virtual void		update(sf::Time dt) override;
	virtual void		handleEvent(const sf::Event& event) override;

private:

	Player&				player;
};

#endif // ONPLATFORMSTATE_HPP
