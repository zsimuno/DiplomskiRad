#include <PauseState.hpp>
#include <Utility.hpp>
#include <State.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


PauseState::PauseState(StateStack& stack, Context context)
	:State(stack, context)
	, pauseMenu(sf::Text("Paused", context.fonts->get(Fonts::ID::Main)), context.window->getView().getSize().x, context.window->getView().getSize().y)
{
	sf::RenderWindow& window = *getContext().window;
	background = sf::RectangleShape(window.getView().getSize() * 6.0f / 8.0f);
	background.setPosition(window.getView().getSize() / 8.0f);
	background.setFillColor(sf::Color(0, 0, 0, 150));

	sf::Font& font = context.fonts->get(Fonts::ID::Main);

	pauseMenu.setPosition(0, 0);

	sf::Text resume("Resume", font);
	pauseMenu.addOption(resume, [this]()
		{
			requestStackPop();
		});

	sf::Text menu("Main menu", font);
	pauseMenu.addOption(menu, [this]()
		{
			requestStateClear();
			requestStackPush(GameStates::ID::Menu);
		});

}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());	

	window.draw(background);
	window.draw(pauseMenu);

}

bool PauseState::update(sf::Time)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	pauseMenu.handleEvent(event);
	return false;
}

