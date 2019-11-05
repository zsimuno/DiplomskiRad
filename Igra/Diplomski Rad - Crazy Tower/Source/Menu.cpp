#include <Menu.hpp>
#include <Utility.hpp>

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RenderTexture.hpp>
#include <iostream>



Menu::Menu(sf::Text menuTitle, float menuWidth, float menuHeight)
	: title(menuTitle)
	, width(menuWidth)
	, height(menuHeight)
	, optionYPosition(menuHeight / 3)
	, selectedOptionIndex(0)
{
	title.setOutlineColor(sf::Color::White);
	title.setOutlineThickness(3);
	title.setCharacterSize(150);
	title.setFillColor(sf::Color(0x01579BFF));
	title.rotate(10);
}

void Menu::addOption(sf::Text optionText, MenuOption::OnClickFunction onClick)
{
	options.push_back(MenuOption(optionText, sf::Vector2f(0.f, optionYPosition), onClick));
	optionYPosition += MenuOption::menuOptionHeight + 15.f;

	if (options.size() == 1)
	{
		options[selectedOptionIndex].select();
	}
}

void Menu::next()
{
	options[selectedOptionIndex].deselect();

	selectedOptionIndex = (selectedOptionIndex + 1) % options.size();

	options[selectedOptionIndex].select();
}

void Menu::previous()
{
	options[selectedOptionIndex].deselect();

	selectedOptionIndex = (selectedOptionIndex - 1) % options.size();

	options[selectedOptionIndex].select();
}


void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (const MenuOption& option : options)
	{
		target.draw(option, states);
	}
	
	target.draw(title, states);
}

void Menu::handleEvent(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
		for (size_t i = 0; i < options.size(); ++i)
		{
			if (options[i].contains(sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y)))
			{
				options[selectedOptionIndex].deselect();
				selectedOptionIndex = i;
				options[selectedOptionIndex].select();
				return;
			}
		}
		break;

	case sf::Event::MouseButtonPressed:
		// Mouse can only be pressed on the selected option
		if (options[selectedOptionIndex].contains(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)))
		{
			options[selectedOptionIndex].click();
		}
		break;

	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
		{
			options[selectedOptionIndex].click();
		}
		else if (event.key.code == sf::Keyboard::Up)
		{
			previous();
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			next();
		}
		break;
	}


}

