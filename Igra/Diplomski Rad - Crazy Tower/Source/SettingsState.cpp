#include <SettingsState.hpp>
#include <Utility.hpp>
#include <State.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context context)
	:State(stack, context)
	, settingsMenu(sf::Text("Settings", context.fonts->get(Fonts::ID::Main)), context.window->getView().getSize().x, context.window->getView().getSize().y)
{
	// Set background texture
	sf::Texture& texture = context.textures->get(Textures::ID::Tower);
	sf::IntRect textureRect(0, 0, (int)context.window->getView().getSize().x, (int)context.window->getView().getSize().y);
	texture.setRepeated(true);
	background.setTexture(texture);
	background.setTextureRect(textureRect);

	sf::Font& font = context.fonts->get(Fonts::ID::Main);

	settingsMenu.setPosition(context.window->getView().getSize().x / 3, 120.f);

	sf::Text resume("Volume", font);
	settingsMenu.addOption(resume, [this]()
		{
			
		});

	sf::Text resume("Character", font);
	settingsMenu.addOption(resume, [this]()
		{

		});

	sf::Text resume("Starting floor", font);
	settingsMenu.addOption(resume, [this]()
		{

		});

	sf::Text menu("Go Back", font);
	settingsMenu.addOption(menu, [this]()
		{
			stackPop();
		});

}

void SettingsState::draw()
{
	context.window->draw(background);
	context.window->draw(settingsMenu);
}

bool SettingsState::update(sf::Time)
{
	return false;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	settingsMenu.handleEvent(event);
	return false;
}

