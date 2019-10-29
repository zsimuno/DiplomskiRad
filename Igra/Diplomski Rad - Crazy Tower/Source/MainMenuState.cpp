#include <MainMenuState.hpp>

MenuMenuState::MenuMenuState(StateStack& stack, Context context)
	:State(stack, context)
{
}


void MenuMenuState::draw()
{
}

bool MenuMenuState::update(sf::Time dt)
{
	return false;
}

bool MenuMenuState::handleEvent(const sf::Event& event)
{
	return false;
}

void MenuMenuState::updateOptionText()
{
}

