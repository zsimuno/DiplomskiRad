#ifndef SETTINGSSTATE_HPP
#define SETTINGSSTATE_HPP

#include <State.hpp>
#include <Menu.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class SettingsState : public State
{
public:
						SettingsState(StateStack& stack, Context context);

	virtual void		draw() override;
	virtual bool		update(sf::Time dt) override;
	virtual bool		handleEvent(const sf::Event& event) override;

private:
	Menu				settingsMenu;
	sf::Sprite			background;
};

#endif // SETTINGSSTATE_HPP