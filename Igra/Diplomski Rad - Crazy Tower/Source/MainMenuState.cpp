#include <MainMenuState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

MainMenuState::MainMenuState(StateStack& stack, Context context)
	:State(stack, context)
	, mainMenu(sf::Text("Crazy Tower", context.fonts->get(Fonts::ID::Main), 100), context.window->getView().getSize().x, context.window->getView().getSize().y)
	, background()
	, playerSprite(context.textures->get(Textures::ID::Character))
{
	sf::Font& font = context.fonts->get(Fonts::ID::Main);

	// Set background texture
	sf::Texture& texture = context.textures->get(Textures::ID::Tower);
	sf::IntRect textureRect(0, 0, (int)context.window->getView().getSize().x, (int)context.window->getView().getSize().y);
	texture.setRepeated(true);
	background.setTexture(texture);
	background.setTextureRect(textureRect);

	playerSprite.setTextureRect(sf::IntRect(2, 4, 29, 52));
	playerSprite.setPosition(context.window->getView().getSize().x / 12, context.window->getView().getSize().y / 3);
	playerSprite.setScale(3.f, 3.f);

	mainMenu.setPosition(context.window->getView().getSize().x / 5, 10.f);

	// Create menu buttons
	sf::Text playText("Play", font);
	mainMenu.addOption(playText, [this]()
		{
			stackPop();
			stackPush(GameStates::ID::Game);
		});

	sf::Text instructionsText("Instructions", font);
	mainMenu.addOption(instructionsText, [this]()
		{
			stackPush(GameStates::ID::Instructions);
		});

	sf::Text settingsText("Settings", font);
	mainMenu.addOption(settingsText, [this]()
		{
			stackPush(GameStates::ID::Settings);
		});

	sf::Text exitText("Exit", font);
	mainMenu.addOption(exitText, [this]()
		{
			stackPop();
		});

}

void MainMenuState::draw()
{
	context.window->draw(background);
	context.window->draw(mainMenu);
	context.window->draw(playerSprite);
}

bool MainMenuState::update(sf::Time)
{
	return true;
}

bool MainMenuState::handleEvent(const sf::Event& event)
{
	mainMenu.handleEvent(event);

	return true;
}


