#include <PauseState.hpp>

PauseState::PauseState(StateStack& stack, Context context)
	:State(stack, context)
{
}

void PauseState::draw()
{
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	return false;
}

