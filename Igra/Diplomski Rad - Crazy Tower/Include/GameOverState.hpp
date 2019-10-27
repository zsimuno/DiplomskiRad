#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include<State.hpp>

class GameOverState :
	public State
{
	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent() override;
};

#endif //GAMEOVERSTATE_HPP
