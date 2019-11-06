#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <State.hpp>
#include <Menu.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

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
	sf::Sprite			playerSprite;

	sf::Text			leaderboardsText;
};

#endif // MAINMENUSTATE_HPP