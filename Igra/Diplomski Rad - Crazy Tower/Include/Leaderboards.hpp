#ifndef LEADERBOARDS_HPP
#define LEADERBOARDS_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>

class Leaderboards : private sf::NonCopyable
{
public:
	struct Score
	{
		Score(std::string playerName, int highestFloor, int highestCombo);

		std::string name;
		int floor;
		int combo;
	};

						Leaderboards();
						~Leaderboards();

	bool				checkScore(int floor, int combo);
	void				addNewScore(Score score);
	std::string			getBoardsText();
private:
	void				updateText();

	std::vector<Score>	floorRecords;
	std::vector<Score>	comboRecords;

	std::string			comboStr;
	std::string			floorStr;
};


#endif // LEADERBOARDS_HPP
