#include <Leaderboards.hpp>


Leaderboards::Leaderboards(sf::Font leaderboardsFont)
	:leaderboardsText("", leaderboardsFont)
{

	updateText();
}

void Leaderboards::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(leaderboardsText, states);
}



bool Leaderboards::checkScore(int floor, int combo)
{
	for (auto score : floorRecords)
	{
		if (floor > score.floor)
		{
			return true;
		}
	}

	for (auto score : comboRecords)
	{
		if (floor > score.combo)
		{
			return true;
		}
	}

	return false;
}

void Leaderboards::addNewScore(Score score)
{

	updateText();
}

void Leaderboards::updateText()
{
}

Leaderboards::Score::Score(std::string playerName, int highestFloor, int highestCombo)
	: name(playerName)
	, floor(highestFloor)
	, combo(highestCombo)
{

}
