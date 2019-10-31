#include <Menu.hpp>
#include <Utility.hpp>

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RenderTexture.hpp>
#include <iostream>



Menu::Menu(sf::Text menuTitle, int menuWidth, int menuHeight)
	: title(menuTitle)
	, width(menuWidth)
	, height(menuHeight)
	, optionYPosition(menuHeight / 2)
	, selectedOptionIndex(0)
{
	title.setPosition(200, 100);
}

void Menu::addOption(sf::Text optionText, MenuOption::OnClickFunction onClick)
{
	MenuOption option(optionText, onClick);
	optionYPosition += 20.f;
	option.setPosition(width / 2, optionYPosition);
	options.push_back(option);

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

	std::cout << getPosition().x << ", " << getPosition().y << std::endl;
	std::cout << width << ", " << height << std::endl;

}

void Menu::previous()
{
	options[selectedOptionIndex].deselect();

	selectedOptionIndex = (selectedOptionIndex - 1) % options.size();

	options[selectedOptionIndex].select();
}


void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const MenuOption& option : options)
	{
		target.draw(option, states);
	}
	target.draw(title, states);
}

void Menu::handleEvent(const sf::Event & event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
		for (size_t i = 0; i < options.size(); ++i)
		{
			if (options[i].contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
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
		if (options[selectedOptionIndex].contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
		{
			options[selectedOptionIndex].click();
		}
		break;

	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Return)
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

