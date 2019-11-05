#ifndef LEADERBOARDS_HPP
#define LEADERBOARDS_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>



class Leaderboards : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	struct Score
	{
		Score(std::string playerName, int highestFloor, int highestCombo);

		std::string name;
		int floor;
		int combo;
	};

						Leaderboards(sf::Font leaderboardsFont);
	void				draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool				checkScore(int floor, int combo);
	void				addNewScore(Score score);

private:
	void				updateText();

	std::vector<Score>	floorRecords;
	std::vector<Score>	comboRecords;

	sf::Text			leaderboardsText;
};


#endif // LEADERBOARDS_HPP
