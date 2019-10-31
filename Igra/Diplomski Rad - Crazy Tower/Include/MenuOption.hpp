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

	MenuOption(sf::Text text, OnClickFunction onClick = []() {});

	void					select();
	void					deselect();
	void					click();
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool					contains(sf::Vector2f point);
private:
	OnClickFunction			onClickAction;
	sf::Text				optionText;
	sf::RectangleShape		optionRect;

	
};

#endif // MENUOPTION_HPP