#ifndef MENU_HPP
#define MENU_HPP

#include <MenuOption.hpp>
#include <SoundPlayer.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

class Menu : public sf::Drawable, public sf::Transformable
{
public:

								Menu(sf::Text menuTitle, float menuWidth, float menuHeight, SoundPlayer& player);

	void						addOption(sf::Text optionText, MenuOption::MenuOptionFunction onClick);
	void						addOption(MenuOption option);

	void						addSelectableOption(sf::Text optionText, MenuOption::MenuSelectFunction onLeft, MenuOption::MenuSelectFunction onRight);
	void						addSelectableOption(MenuOption option);

	virtual void				draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void						handleEvent(const sf::Event & event);

private:
	void						next();
	void						previous();

	std::vector<MenuOption>		options;
	sf::Text					title;
	sf::Text					titleShadow;
	float						optionYPosition;
	float						width;
	float						height;

	SoundPlayer&				player;

	int							selectedOptionIndex;

};

#endif // MENU_HPP


