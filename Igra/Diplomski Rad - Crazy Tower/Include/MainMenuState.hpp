#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class MenuMenuState : public State
{
public:
	MenuMenuState();

	virtual void			draw() override;
	virtual bool			update(sf::Time dt) override;
	virtual bool			handleEvent() override;


private:
	sf::Sprite				mBackgroundSprite;
};

#endif // MAINMENUSTATE_HPP