#include <Leaderboards.hpp>

#include <iosfwd>
#include <fstream>
#include <string>
#include <sstream>

#include <cassert>


Leaderboards::Leaderboards()
{
	std::string line;
	std::ifstream infile;
	infile.open("Media/leaderboards.txt");
	std::vector<Score>* scores = &comboRecords;
	int br = 0;
	while (getline(infile, line))
	{
		if (line.find("combo") != -1)
		{
			// Combo records vector already pointed to
			continue;
		}

		if (line.find("floor") != -1)
		{
			scores = &floorRecords;
			continue;
		}

		// Get data from the line
		std::stringstream iss(line);
		int position, floor, combo;
		std::string name;
		iss >> position;
		iss.ignore(1, ' ');
		iss >> floor;
		iss.ignore(1, ' ');
		iss >> combo;
		iss.ignore(1, ' ');
		getline(iss, name);

		scores->push_back(Score(name, floor, combo));
	}
	infile.close();

	assert(comboRecords.size() > 0);
	assert(floorRecords.size() > 0);

	updateText();
}

Leaderboards::~Leaderboards()
{
	std::ofstream myfile("Media/leaderboards.txt");

	if (myfile.is_open())
	{
		myfile << "Highest combo" << std::endl;
		for (std::size_t i = 0; i < comboRecords.size(); ++i)
		{
			myfile << std::to_string(i + 1) << " " << std::to_string(comboRecords[i].floor)
				<< " " << std::to_string(comboRecords[i].combo) << " " << comboRecords[i].name << std::endl;
		}

		myfile << "Highest floor" << std::endl;
		for (std::size_t i = 0; i < floorRecords.size(); ++i)
		{
			myfile << std::to_string(i + 1) << " " << std::to_string(floorRecords[i].floor)
				<< " " << std::to_string(floorRecords[i].combo) << " " << floorRecords[i].name << std::endl;
		}
		myfile.close();
	}

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
	
	for (auto s = comboRecords.begin(); s != comboRecords.end(); ++s)
	{
		if (score.combo > s->combo)
		{
			comboRecords.insert(s, score);
			comboRecords.pop_back();
			break;
		}
	}
	
	for (auto s = floorRecords.begin(); s != floorRecords.end(); ++s)
	{
		if (score.floor > s->floor)
		{
			floorRecords.insert(s, score);
			floorRecords.pop_back();
			break;
		}
	}
	
	updateText();
}

std::string Leaderboards::getBoardsText()
{
	return comboStr + floorStr;
}

void Leaderboards::updateText()
{
	comboStr = "Highest combo\n";
	comboStr += "#\tFl\tCo\tNa\n";
	for (std::size_t i = 0; i < comboRecords.size(); ++i)
	{
		comboStr += std::to_string(i + 1) + "\t" + std::to_string(comboRecords[i].floor)
			+ "\t" + std::to_string(comboRecords[i].combo) + "\t" + comboRecords[i].name + "\n";
	}

	floorStr = "Highest floor\n";
	floorStr += "#\tFl\tCo\tNa\n";
	for (std::size_t i = 0; i < floorRecords.size(); ++i)
	{
		floorStr += std::to_string(i + 1) + "\t" + std::to_string(floorRecords[i].floor)
			+ "\t" + std::to_string(floorRecords[i].combo) + "\t" + floorRecords[i].name + "\n";
	}

}

Leaderboards::Score::Score(std::string playerName, int highestFloor, int highestCombo)
	: name(playerName)
	, floor(highestFloor)
	, combo(highestCombo)
{

}
