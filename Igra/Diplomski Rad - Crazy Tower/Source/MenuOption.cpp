#include <MenuOption.hpp>
#include <Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>


MenuOption::MenuOption(sf::Text text, sf::Vector2f position, OnClickFunction onClick)
	: optionText(text)
	, onClickAction(onClick)
	, optionRect(sf::Vector2f(menuOptionWidth, menuOptionHeight))
	, primaryColor(0x01579BFF)
	, secondaryColor(0x2196F3FF)
	, outlineColor(sf::Color::White)
	, secondaryOutlineColor(0xBBDEFBFF)
{
	this->setPosition(0.f, position.y);
	optionRect.setOutlineThickness(5);
	optionRect.setFillColor(primaryColor);
	optionRect.setOutlineColor(outlineColor);

	optionText.setCharacterSize(2 * menuOptionHeight / 3);
	Utility::centerOrigin(optionText);
	optionText.setPosition(menuOptionWidth / 2, menuOptionHeight / 2);
	optionText.setFillColor(outlineColor);
	optionText.setStyle(sf::Text::Style::Bold);

}

void MenuOption::select()
{
	optionRect.setOutlineColor(outlineColor);
	optionRect.setFillColor(secondaryColor);
	optionText.setFillColor(outlineColor);
}

void MenuOption::deselect()
{
	optionRect.setOutlineColor(secondaryOutlineColor);
	optionRect.setFillColor(primaryColor);
	optionText.setFillColor(secondaryOutlineColor);
}

void MenuOption::click()
{
	onClickAction();
}

void MenuOption::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(optionRect, states);
	target.draw(optionText, states);
}

bool MenuOption::contains(sf::Vector2f point)
{
	return optionRect.getGlobalBounds().contains(point);
}
