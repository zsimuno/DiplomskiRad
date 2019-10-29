#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>
#include <State.hpp>

class StateStack : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};

public:
	explicit			StateStack(State::Context context);

	template <typename T>
	void				registerState(GameStates::ID stateID);

	void				update(sf::Time dt);
	void				draw();
	void				handleEvent(const sf::Event& event);

	void				pushState(GameStates::ID stateID);
	void				popState();
	void				clearStates();

	bool				isEmpty() const;

private:
	State::Ptr			createState(GameStates::ID stateID);
	void				applyPendingChanges();

private:
	struct PendingChange
	{
		explicit			PendingChange(Action action, GameStates::ID stateID = GameStates::None);

		Action				action;
		GameStates::ID		stateID;
	};

private:
	std::vector<State::Ptr>								mStack;
	std::vector<PendingChange>							mPendingList;

	State::Context										mContext;
	std::map<GameStates::ID, std::function<State::Ptr()>>	mFactories;
};

template <typename T>
void StateStack::registerState(GameStates::ID stateID)
{
	mFactories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, mContext));
	};
}

#endif // STATESTACK_HPP