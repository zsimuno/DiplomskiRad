#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include<State.hpp>

class PauseState :
	public State
{
	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;
};

#endif // PAUSESTATE_HPP