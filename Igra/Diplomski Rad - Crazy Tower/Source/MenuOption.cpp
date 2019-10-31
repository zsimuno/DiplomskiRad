#include <MenuOption.hpp>
#include <Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>


MenuOption::MenuOption(sf::Text text, OnClickFunction onClick)
	: optionText(text)
	, onClickAction(onClick)
	, optionRect(sf::Vector2f(200, 50))
{
	optionRect.setOutlineThickness(4);
	optionRect.setFillColor(sf::Color::Cyan);
	optionRect.setOutlineColor(sf::Color::Black);

	Utility::centerOrigin(optionText);
	optionText.setPosition(100, 25);
}

void MenuOption::select()
{
	optionRect.setOutlineColor(sf::Color::White);
	optionText.setFillColor(sf::Color::White);
	std::cout << getPosition().x << ", " << getPosition().y << std::endl;
}

void MenuOption::deselect()
{
	optionRect.setOutlineColor(sf::Color::Black);
	optionText.setFillColor(sf::Color::Black);
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
