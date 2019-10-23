#ifndef STATE_HPP
#define STATE_HPP

#include <SFML\System\Time.hpp>
#include <SFML\Window\Event.hpp>

class State
{
	public:
		virtual void		draw() = 0;
		virtual bool		update(sf::Time dt) = 0;
		virtual bool		handleEvent(const sf::Event& event) = 0;
};

#endif // STATE_HPP