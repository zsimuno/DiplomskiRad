#ifndef PLAYERSTATE_HPP
#define PLAYERSTATE_HPP

#include <SFML\System\Time.hpp>
#include <SFML\Window\Event.hpp>

class PlayerState
{
public:
	virtual void		draw() = 0;
	virtual void		update(sf::Time dt) = 0;
	virtual void		handleEvent(const sf::Event& event) = 0;
};

#endif // PLAYERSTATE_HPP
