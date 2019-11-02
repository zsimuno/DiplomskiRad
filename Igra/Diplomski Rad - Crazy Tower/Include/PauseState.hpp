#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include <State.hpp>
#include <StateStack.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Menu.hpp>

class PauseState :
	public State
{
public:
	PauseState(StateStack& stack, Context context);

	virtual void		draw() override;
	virtual bool		update(sf::Time dt) override;
	virtual bool		handleEvent(const sf::Event& event) override;

private:
	sf::RectangleShape	background;
	Menu				pauseMenu;
};

#endif // PAUSESTATE_HPP