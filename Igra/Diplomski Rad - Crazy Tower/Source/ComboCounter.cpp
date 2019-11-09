#include <ComboCounter.hpp>
#include <Tower.hpp>

ComboCounter::ComboCounter(State::Context gameContext, Tower& gameTower, Player& pl)
	:tower(gameTower)
	, player(pl)
	, comboText("   0 \n Floors", gameContext.fonts->get(Fonts::ID::Main))
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

	comboBarBack.setFillColor(gameContext.colorHolder->get(Colors::ID::BackBarColor));
	comboBarFront.setFillColor(gameContext.colorHolder->get(Colors::ID::FrontBarColor));
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

	// Update combo bar
	float timerDiff = (comboTimer.getElapsedTime().asSeconds() * (comboBarHeight / 3));
	comboBarFront.setPosition(5.f, 5.f + timerDiff);
	comboBarFront.setSize(sf::Vector2f(comboBarWidth, comboBarHeight - timerDiff));

	// Update combo text
	if (player.getCombo() == 0)
	{
		comboText.setString("");
	}
	else
	{
		comboText.setString("   " + std::to_string(player.getCombo()) + "\n Floors");
	}

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

