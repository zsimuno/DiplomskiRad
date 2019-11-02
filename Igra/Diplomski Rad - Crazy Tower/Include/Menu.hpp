#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>

#include <MenuOption.hpp>
#include <SFML/Window/Event.hpp>

class Menu : public sf::Drawable, public sf::Transformable
{
public:
	Menu(sf::Text menuTitle, float menuWidth, float menuHeight);

	void						addOption(sf::Text optionText, MenuOption::OnClickFunction onClick);
	virtual void				draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void						handleEvent(const sf::Event & event);

private:
	void						next();
	void						previous();

	std::vector<MenuOption>		options;
	sf::Text					title;
	float						optionYPosition;
	float						width;
	float						height;
	int							selectedOptionIndex;

};

#endif // MENU_HPP


