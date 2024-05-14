#pragma once
#include <string>

namespace ApplesGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const float INITIAL_SPEED = 100.f; // Pixels per second
	const float PLAYER_SIZE = 20.f;

	const float ACCELERATION = 20.f; // Pixels per second

	const int NUM_APPLES_MIN = 10;
	const int NUM_APPLES_MAX = 20;
	const float APPLE_SIZE = 20.f;
	const float PAUSE_LENGTH = 3.f;
	const int NUM_ROCKS = 10;
	const float ROCK_SIZE = 30.f;

	//setting up[ random scores for players in scoreboard 
	const int player1Score = 1 + (rand() % 30);
	const int player2Score = 1 + (rand() % 30);
	const int player3Score = 1 + (rand() % 30);

	const int SCOREBOARD_SIZE = 4; //size of scoreboard (must match num of players on it)
}