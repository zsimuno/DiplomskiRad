#include <MainMenuState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

MainMenuState::MainMenuState(StateStack& stack, Context context)
	:State(stack, context)
	, mainMenu(sf::Text("Main Menu", context.fonts->get(Fonts::ID::Main)),  context.window->getView().getSize().x, context.window->getView().getSize().y)
{
	sf::Font& font = context.fonts->get(Fonts::ID::Main);

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
	sf::RectangleShape rect(sf::Vector2f((float)getContext().window->getSize().x, (float)getContext().window->getSize().y));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Blue);
	getContext().window->draw(rect);

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


