#include "..\Include\StateStack.hpp"


StateStack::StateStack(State::Context context)
	: mStack()
	, mPendingList()
	, mContext(context)
	, mFactories()
{
}

void StateStack::update(sf::Time dt)
{

}

void StateStack::draw()
{

}

void StateStack::handleEvent(const sf::Event& event)
{
}

void StateStack::pushState(GameStates::ID stateID)
{
}

void StateStack::popState()
{
}

void StateStack::clearStates()
{
}

bool StateStack::isEmpty() const
{
	return false;
}

State::Ptr StateStack::createState(GameStates::ID stateID)
{
	return State::Ptr();
}

void StateStack::applyPendingChanges()
{
}

StateStack::PendingChange::PendingChange(Action action, GameStates::ID stateID)
{
}
