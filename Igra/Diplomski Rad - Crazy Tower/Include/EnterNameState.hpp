#ifndef ENTERNAMESTATE_HPP
#define ENTERNAMESTATE_HPP

#include <State.hpp>
#include <Menu.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>


class EnterNameState : public State
{
public:
						EnterNameState(StateStack& stack, Context context);

	virtual void		draw() override;
	virtual bool		update(sf::Time dt) override;
	virtual bool		handleEvent(const sf::Event& event) override;

private:
	sf::RectangleShape	background;

	sf::Clock			blinkTimer;

	std::string			nameInputString;

	sf::Text			title;
	sf::Text			nameInput;
	sf::Text			nameEnterLabel;

	int					currentCharacter;

};

#endif //ENTERNAMESTATE_HPP
