#include <ComboCounter.hpp>
#include <Tower.hpp>

ComboCounter::ComboCounter(State::Context gameContext, Tower& gameTower, Player& pl)
	:tower(gameTower)
	, player(pl)
	, comboText("   0 \nFloors", gameContext.fonts->get(Fonts::ID::Main))
	, comboTimer()
	, timerStarted(false)
	, comboNumber(0)
	, comboBarBack(sf::Vector2f((float)comboBarWidth + 10.f, (float)comboBarHeight + 10.f))
	, comboBarFront(sf::Vector2f((float)comboBarWidth, 0.f))
{
	Utility::centerOrigin(comboText);

	comboText.setPosition(comboBarWidth/2, comboBarHeight + 45);

	comboText.setCharacterSize(40);
	comboText.setOutlineColor(sf::Color::Black);
	comboText.setOutlineThickness(2);

	comboBarFront.setPosition(5.f, 5.f);

	comboBarBack.setFillColor(sf::Color(0x009688FF));
	comboBarFront.setFillColor(sf::Color(0x81D4FAFF));
}

void ComboCounter::updateCurrent(sf::Time dt)
{
	int currentCombo = player.getCombo();

	if (currentCombo > 0)
	{
		// Restart if player jumped on new platform
		if (comboNumber != currentCombo)
		{
			comboTimer.restart();
		}
		else if (comboTimer.getElapsedTime().asSeconds() >= 3)
		{
			// Player has 3 seconds to continue the combo
			player.endCombo();
			comboTimer.restart();
		}
		comboNumber = currentCombo;
	}
	else
	{
		comboTimer.restart();
	}

	float timerDiff = (comboTimer.getElapsedTime().asSeconds() * (comboBarHeight / 3));
	comboBarFront.setPosition(5.f, 5.f + timerDiff);
	comboBarFront.setSize(sf::Vector2f(comboBarWidth, comboBarHeight - timerDiff));
	comboText.setString("   " + std::to_string(player.getCombo()) + "\nFloors");

}

void ComboCounter::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(comboBarBack, states);
	target.draw(comboBarFront, states);

	if (comboNumber > 0)
	{
		target.draw(comboText, states);
	}
}

void ComboCounter::initialize()
{
}

