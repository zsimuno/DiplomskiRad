#ifndef INSTRUCTIONSSTATE_HPP
#define INSTRUCTIONSSTATE_HPP

#include <State.hpp>
#include <Menu.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class InstructionsState : public State
{
public:
	InstructionsState(StateStack& stack, Context context);

	virtual void		draw() override;
	virtual bool		update(sf::Time dt) override;
	virtual bool		handleEvent(const sf::Event& event) override;

private:

	sf::Sprite			keyboardInstructions;
	sf::Sprite			comboInstructions;
	sf::Sprite			speedInstructions;
	sf::Sprite			background;
};

#endif // INSTRUCTIONSSTATE_HPP