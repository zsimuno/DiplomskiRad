#include <MenuOption.hpp>
#include <Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

// TODO: Mozda mis da registrira lijevo desno

MenuOption::MenuOption(sf::Text text, MenuOptionFunction onClick)
	: optionText(text)
	, onClickAction(onClick)
	, optionRect(sf::Vector2f(menuOptionWidth, menuOptionHeight))
	, shadowRect(sf::Vector2f(menuOptionWidth, menuOptionHeight))
	, primaryColor(0x01579BFF)
	, secondaryColor(0x2196F3FF)
	, outlineColor(sf::Color::White)
	, secondaryOutlineColor(0xBBDEFBFF)
	, onLeftRightSet(false)
	, arrowLeft(text)
	, arrowRight(text)
{

	optionRect.setOutlineThickness(5);
	optionRect.setFillColor(primaryColor);
	optionRect.setOutlineColor(outlineColor);

	optionText.setCharacterSize(2 * menuOptionHeight / 3);
	Utility::centerOrigin(optionText);
	optionText.setPosition(menuOptionWidth / 2, menuOptionHeight / 2);
	optionText.setFillColor(secondaryOutlineColor);
	optionText.setStyle(sf::Text::Style::Bold);

	shadowRect.setFillColor(sf::Color(0, 0, 0, 150));
	shadowRect.setPosition(optionRect.getPosition() + sf::Vector2f(10.f, 10.f));

}

MenuOption::MenuOption(sf::Text text, MenuSelectFunction onLeft, MenuSelectFunction onRight)
	: MenuOption(text)
{
	setLeftRight(onLeft, onRight);
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

void MenuOption::setLeftRight(MenuSelectFunction onLeft, MenuSelectFunction onRight)
{
	onLeftAction = onLeft;
	onRightAction = onRight;
	onLeftRightSet = true;

	arrowLeft.setString("<");
	arrowLeft.setCharacterSize(2 * menuOptionHeight / 3);
	Utility::centerOrigin(arrowLeft);
	arrowLeft.setPosition(arrowLeft.getLocalBounds().width + 10, menuOptionHeight / 2);
	arrowLeft.setFillColor(outlineColor);
	arrowLeft.setStyle(sf::Text::Style::Bold);

	arrowRight.setString(">");
	arrowRight.setCharacterSize(2 * menuOptionHeight / 3);
	Utility::centerOrigin(arrowRight);
	arrowRight.setPosition(menuOptionWidth - arrowRight.getLocalBounds().width - 10, menuOptionHeight / 2);
	arrowRight.setFillColor(outlineColor);
	arrowRight.setStyle(sf::Text::Style::Bold);
}

void MenuOption::pressLeft()
{
	if (onLeftRightSet)
	{
		onLeftAction(this);
	}
}

void MenuOption::pressRight()
{
	if (onLeftRightSet)
	{
		onRightAction(this);
	}
}

void MenuOption::setString(std::string text)
{
	optionText.setString(text);
	Utility::centerOrigin(optionText);
}

void MenuOption::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(shadowRect, states);
	target.draw(optionRect, states);
	target.draw(optionText, states);

	if (onLeftRightSet)
	{
		target.draw(arrowLeft, states);
		target.draw(arrowRight, states);
	}
}


bool MenuOption::contains(sf::Vector2f point, sf::Vector2f menuPosition)
{
	return sf::FloatRect((menuPosition + this->getPosition() + optionRect.getPosition()), optionRect.getSize()).contains(point);
}

bool MenuOption::leftContains(sf::Vector2f point, sf::Vector2f menuPosition)
{
	return sf::FloatRect((menuPosition + this->getPosition() + optionRect.getPosition()), sf::Vector2f(optionRect.getSize().x / 2, optionRect.getSize().y)).contains(point);
}
