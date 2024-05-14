#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Game.h"

using namespace ApplesGame;

int main()
{
	int seed = (int)time(nullptr);
	srand(seed);

	// Init window
	sf::RenderWindow window(sf::VideoMode(ApplesGame::SCREEN_WIDTH, ApplesGame::SCREEN_HEIGHT), "Apples game!");

	//Game Initialization
	ApplesGame::Game* game = new ApplesGame::Game();
	InitGame(*game);

	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Main loop
	while (window.isOpen())
	{
		// Reduce framrate to not spam CPU and GPU
		sf::sleep(sf::milliseconds(15));

		HandleWindowEvents(*game, window);

		if (!window.isOpen())
		{
			break;
		}

		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		

		if (UpdateGame(*game, deltaTime))
		{
			window.clear();
			
			DrawGame(*game, window);

			window.display();
		}
		else
		{
			window.close();
		}

	}
	//Deinitialization
	DeinitializeGame(*game);
	delete game;
	game = nullptr;
	
	
	return 0;
}
