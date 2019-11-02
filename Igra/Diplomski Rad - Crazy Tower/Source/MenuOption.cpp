#include <MenuOption.hpp>
#include <Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>


MenuOption::MenuOption(sf::Text text, sf::Vector2f position, OnClickFunction onClick)
	: optionText(text)
	, onClickAction(onClick)
	, optionRect(sf::Vector2f(200, 40))
	, primaryColor(69, 39, 160)
	, secondaryColor(179, 157, 219)
	, outlineColor(179, 136, 255)
{
	this->setPosition(position);
	optionRect.setOutlineThickness(5);
	optionRect.setFillColor(primaryColor);
	optionRect.setOutlineColor(outlineColor);
	optionRect.setPosition(position);

	Utility::centerOrigin(optionText);
	optionText.setPosition(position + sf::Vector2f(100, 20));
	optionText.setFillColor(outlineColor);

}

void MenuOption::select()
{
	optionRect.setOutlineColor(sf::Color::White);
	optionRect.setFillColor(secondaryColor);
	optionText.setFillColor(sf::Color::White);
}

void MenuOption::deselect()
{
	optionRect.setOutlineColor(outlineColor);
	optionRect.setFillColor(primaryColor);
	optionText.setFillColor(outlineColor);
}

void MenuOption::click()
{
	onClickAction();
}

void MenuOption::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(optionRect, states);
	target.draw(optionText, states);
}

bool MenuOption::contains(sf::Vector2f point)
{
	return optionRect.getGlobalBounds().contains(point);
}
