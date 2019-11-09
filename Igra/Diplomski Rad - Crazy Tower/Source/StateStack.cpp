#include <StateStack.hpp>

#include <assert.h>

StateStack::StateStack(State::Context context)
	: stack()
	, pending()
	, context(context)
	, states()
{
}

void StateStack::update(sf::Time dt)
{
	for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	for(State::StatePointer & state: stack)
		state->draw();
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			break;
	}

	applyPendingChanges();
}

void StateStack::pushState(GameStates::ID stateID)
{
	pending.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::popState()
{
	pending.push_back(PendingChange(Action::Pop));
}

void StateStack::clearStates()
{
	pending.push_back(PendingChange(Action::Clear));
}

bool StateStack::isEmpty() const
{
	return stack.empty();
}

State::StatePointer StateStack::createState(GameStates::ID stateID)
{
	auto found = states.find(stateID);
	assert(found != states.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for(PendingChange change: pending)
	{
		switch (change.action)
		{
		case Action::Push:
			stack.push_back(createState(change.stateID));
			break;

		case Action::Pop:
			stack.pop_back();
			break;

		case Action::Clear:
			stack.clear();
			break;
		}
	}

	pending.clear();
}

StateStack::PendingChange::PendingChange(Action action, GameStates::ID stateID)
	: action(action)
	, stateID(stateID)
{
}
