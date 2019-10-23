#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include<State.hpp>

class GameState :
	public State
{
	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;
};

#endif // GAMESTATE_HPP