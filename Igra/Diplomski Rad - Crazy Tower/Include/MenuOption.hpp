#ifndef MENUOPTION_HPP
#define MENUOPTION_HPP
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <functional>

class MenuOption : public sf::Drawable , public sf::Transformable
{
public:
	using MenuOptionFunction = std::function<void()>;
	using MenuSelectFunction = std::function<void(MenuOption*)>;

	static const int		menuOptionHeight = 60;
	static const int		menuOptionWidth = 400;

							MenuOption(sf::Text text, MenuOptionFunction onClick = []() {});
							MenuOption(sf::Text text, MenuSelectFunction onLeft, MenuSelectFunction onRight);

	void					select();
	void					deselect();
	void					click();

	void					setLeftRight(MenuSelectFunction onLeft, MenuSelectFunction onRight);

	void					pressLeft();
	void					pressRight();

	void					setString(std::string text);

	bool					contains(sf::Vector2f point, sf::Vector2f menuPosition);
	bool					leftContains(sf::Vector2f point, sf::Vector2f menuPosition);

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	MenuOptionFunction		onClickAction;
	MenuSelectFunction		onLeftAction;
	MenuSelectFunction		onRightAction;

	bool					onLeftRightSet;

	sf::Text				optionText;
	sf::Text				arrowLeft;
	sf::Text				arrowRight;
	sf::RectangleShape		optionRect;
	sf::RectangleShape		shadowRect;
	sf::Color				primaryColor;
	sf::Color				secondaryColor;
	sf::Color				outlineColor;
	sf::Color				secondaryOutlineColor;

	
};

#endif // MENUOPTION_HPP