#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include<State.hpp>

class PauseState :
	public State
{
	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent() override;
};

#endif // PAUSESTATE_HPP