#include <MainMenuState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

MainMenuState::MainMenuState(StateStack& stack, Context context)
	:State(stack, context)
	, mainMenu(sf::Text("Crazy Tower", context.fonts->get(Fonts::ID::Main)), context.window->getView().getSize().x, context.window->getView().getSize().y)
	, background()
{
	sf::Font& font = context.fonts->get(Fonts::ID::Main);

	sf::Texture& texture = context.textures->get(Textures::ID::Tower);
	sf::IntRect textureRect(0, 0, context.window->getView().getSize().x, context.window->getView().getSize().y);
	texture.setRepeated(true);
	background.setTexture(texture);
	background.setTextureRect(textureRect);

	mainMenu.setPosition(0, 0);

	sf::Text playText("Play", font);
	mainMenu.addOption(playText, [this]()
		{
			requestStackPop();
			requestStackPush(GameStates::ID::Game);
		});

	sf::Text exitText("Exit", font);
	mainMenu.addOption(exitText, [this]()
		{
			requestStackPop();
		});

}

void MainMenuState::draw()
{
	getContext().window->draw(background);

	getContext().window->setView(getContext().window->getDefaultView());
	getContext().window->draw(mainMenu);
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


