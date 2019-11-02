#ifndef MENUOPTION_HPP
#define MENUOPTION_HPP
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <functional>

class MenuOption : public sf::Drawable , public sf::Transformable
{
public:
	using OnClickFunction = std::function<void()>;

	MenuOption(sf::Text text, sf::Vector2f position, OnClickFunction onClick = []() {});

	void					select();
	void					deselect();
	void					click();
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool					contains(sf::Vector2f point);
private:
	OnClickFunction			onClickAction;
	sf::Text				optionText;
	sf::RectangleShape		optionRect;
	sf::Color				primaryColor;
	sf::Color				secondaryColor;
	sf::Color				outlineColor;

	
};

#endif // MENUOPTION_HPP