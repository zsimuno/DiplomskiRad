#include <MainMenuState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

MainMenuState::MainMenuState(StateStack& stack, Context context)
	:State(stack, context)
	, mainMenu(sf::Text("Crazy Tower", context.fonts->get(Fonts::ID::Main), 100), context.window->getView().getSize().x, context.window->getView().getSize().y)
	, background()
{
	sf::Font& font = context.fonts->get(Fonts::ID::Main);

	// Set background texture
	sf::Texture& texture = context.textures->get(Textures::ID::Tower);
	sf::IntRect textureRect(0, 0, (int)context.window->getView().getSize().x, (int)context.window->getView().getSize().y);
	texture.setRepeated(true);
	background.setTexture(texture);
	background.setTextureRect(textureRect);

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


