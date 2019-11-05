#ifndef STATE_HPP
#define STATE_HPP

#include <GameStates.hpp>
#include <ResourceIdentifiers.hpp>

#include <SFML\System\Time.hpp>
#include <SFML\Window\Event.hpp>


namespace sf
{
	class RenderWindow;
}

class StateStack;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Textures::ID& character);

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
		Textures::ID* currentCharacterID;
	};

public:
	State(StateStack& stack, Context context);
	virtual void		draw() = 0;
	virtual bool		update(sf::Time dt) = 0;
	virtual bool		handleEvent(const sf::Event& event) = 0;

protected:
	void				stackPush(GameStates::ID stateID);
	void				stackPop();
	void				stackClear();

	Context				context;
	
private:
	StateStack*			stack;
	
};

#endif // STATE_HPP