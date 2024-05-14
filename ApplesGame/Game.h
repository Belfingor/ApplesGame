#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Math.h"
#include <SFML/Audio.hpp>
#include <cassert>
#include <map>
#include <unordered_map>

namespace ApplesGame
{	
	//-----------------------------------------------
	//Creating bitMasks for game modes
	enum class GameModes: std::uint8_t
	{
		ENDLESS_APPLES_ON = 1 << 0,
		ACCELERATION_ON = 1 << 1,

		Default = ENDLESS_APPLES_ON + ACCELERATION_ON
	};

	//-----------------------------------------------
	//Creating Stack for GameStates
	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		Scoreboard,
		ExitDialog
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};
	
	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Swith
	};
	//-----------------------------------------------

	// Main Game Structure
	struct Game
	{
		Rectangle screenRect;

		// Setting GameMode to default settings
		GameModes modes = GameModes::Default;
		
		// Global Game data
		bool isGameFinished = false;
		bool isGameWon = false;
		sf::RectangleShape background;
		std::unordered_map<std::string, int> scoreboard;
		std::multimap<int, std::string> sortedScoreboard; //unordered_map doesnt sort so will sort it here by swapping key and value 

		// GameState Stack data
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;
		int numEatenApples = 0;

		// Resources		
		sf::Text gameMenuTextMode1;
		sf::Text gameMenuTextMode2;
		
	};

	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible);
	void PopGameState(Game& game);
	void SwitchGameState(Game& game, GameStateType newState);
	bool UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void ShutdownGame(Game& game);
	void InitGameState(Game& game, GameState& state);
	void ShutDownGameState (Game& game, GameState& state);
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event);
	void UpdateGameState(Game& game, GameState& state, float deltaTime);
	void SortScoreBoard(Game& game);
	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window);
	



	void InitGame(Game& game);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	//void GameMenu(Game& game);    // will play with that later
	void DeinitializeGame(Game& game);
}


