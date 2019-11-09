#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <State.hpp>
#include <Tower.hpp>
#include <StateStack.hpp>

class GameState : public State
{
public:
						GameState(StateStack& stack, Context context);

	virtual void		draw() override;
	virtual bool		update(sf::Time dt) override;
	virtual bool		handleEvent(const sf::Event& event) override;
private:
	Tower				tower;
};

#endif // GAMESTATE_HPP