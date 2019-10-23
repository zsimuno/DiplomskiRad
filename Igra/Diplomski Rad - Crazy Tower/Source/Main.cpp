#include <SFML/Graphics.hpp>
#include <Game.hpp>
#include <iostream>
int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::exception & e)
	{
		std::cout << "\nError in the game: \n" << e.what() << std::endl;
	}
	
}