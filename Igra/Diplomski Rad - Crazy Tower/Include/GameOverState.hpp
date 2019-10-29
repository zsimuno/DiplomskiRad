#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include<State.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class GameOverState :
	public State
{
public:
	GameOverState(StateStack& stack, Context context);

	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

private:
	sf::Text			gameOverText;
	sf::Time			elapsedTime;
	sf::RectangleShape	background;

};

#endif //GAMEOVERSTATE_HPP
