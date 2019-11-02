#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Menu.hpp"

class MainMenuState : public State
{
public:
	MainMenuState(StateStack& stack, Context context);

	virtual void		draw() override;
	virtual bool		update(sf::Time dt) override;
	virtual bool		handleEvent(const sf::Event& event) override;

private:
	Menu				mainMenu;
	sf::Sprite			background;
};

#endif // MAINMENUSTATE_HPP