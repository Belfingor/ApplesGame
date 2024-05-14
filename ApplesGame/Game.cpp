#include "Game.h"
#include <cassert>
#include <string>
#include <algorithm>
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateExitDialog.h"
#include "GameStateMainMenu.h"
#include "GameStateScoreboard.h"


namespace ApplesGame
{
	//------------------------------------------------------------------------
	// Defining Game State Stack logic
	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible)
	{
		game.pendingGameStateType = stateType;
		game.pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		game.gameStateChangeType = GameStateChangeType::Push;
	}

	void PopGameState(Game& game)
	{
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Pop;
	}

	void SwitchGameState(Game& game, GameStateType newState)
	{
		game.pendingGameStateType = newState;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Swith;
	}
	//------------------------------------------------------------------------


	bool UpdateGame(Game& game, float deltaTime)
	{
		if (game.gameStateChangeType == GameStateChangeType::Swith)
		{
			// Shutdown all game states
			while (game.gameStateStack.size() > 0)
			{
				ShutDownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}
		else if (game.gameStateChangeType == GameStateChangeType::Pop)
		{
			// Shuttdown only current game state
			if (game.gameStateStack.size() > 0)
			{
				ShutDownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}
		// Init new game state if needed
		if (game.pendingGameStateType != GameStateType::None)
		{
			game.gameStateStack.push_back({ game.pendingGameStateType, nullptr, game.pendingGameStateIsExclusivelyVisible });
			InitGameState(game, game.gameStateStack.back());
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;

		if (game.gameStateStack.size() > 0)
		{
			UpdateGameState(game, game.gameStateStack.back(), deltaTime);
			return true;
		}
		return false;

	}


	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		if (game.gameStateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = game.gameStateStack.rbegin(); it != game.gameStateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}
			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				DrawGameState(game, **it, window);
			}
		}
	}
	void ShutdownGame(Game& game)
	{
		// Shutdown all game states
		while (game.gameStateStack.size() > 0)
		{
			ShutDownGameState(game, game.gameStateStack.back());
			game.gameStateStack.pop_back();
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
	}
	void InitGameState(Game& game, GameState& state) 
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			state.data = new GameStatMainMenuData();
			InitGameStateMainMenu(*(GameStatMainMenuData*)state.data, game);
			break;
		}
		case GameStateType::Playing:
		{
			state.data = new GameStatePlayingData();
			InitGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			break;
		}
		case GameStateType::GameOver:
		{
			state.data = new GameStateGameOverData();
			InitGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			break;
		}
		case GameStateType::Scoreboard:
		{
			state.data = new GameStateScoreboardData();
			InitGameStateScoreboard(*(GameStateScoreboardData*)state.data, game);
			break;
		}
		case GameStateType::ExitDialog:
		{
			state.data = new GameStateExitDialogData();
			InitGameStateExitDialog(*(GameStateExitDialogData*)state.data, game);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}
	void ShutDownGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			ShutDownGameStateMainMenu(*(GameStatMainMenuData*)state.data, game);
			delete (GameStatMainMenuData*)state.data;
			break;
		}
		case GameStateType::Playing:
		{
			ShutDownGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			delete (GameStatePlayingData*)state.data;
			break;
		}
		case GameStateType::GameOver:
		{
			ShutDownGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			delete (GameStateGameOverData*)state.data;
			break;
		}
		case GameStateType::Scoreboard:
		{
			ShutDownGameStateScoreboard(*(GameStateScoreboardData*)state.data, game);
			delete (GameStateScoreboardData*)state.data;
			break;
		}
		case GameStateType::ExitDialog:
		{
			ShutDownGameStateExitDialog(*(GameStateExitDialogData*)state.data, game);
			delete (GameStateExitDialogData*)state.data;
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			HandleGameStateMainMenuWindowEvent(*(GameStatMainMenuData*)state.data, game, event);
			break;
		}
		case GameStateType::Playing:
		{
			HandleGameStatePlayingWindowEvent(*(GameStatePlayingData*)state.data, game, event);
			break;
		}
		case GameStateType::GameOver:
		{
			HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)state.data, game, event);
			break;
		}
		case GameStateType::Scoreboard:
		{
			HandleGameStateScoreboardWindowEvent(*(GameStateScoreboardData*)state.data, game, event);
			break;
		}
		case GameStateType::ExitDialog:
		{
			HandleGameStateExitDialogWindowEvent(*(GameStateExitDialogData*)state.data, game, event);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}
	void UpdateGameState(Game& game, GameState& state, float deltaTime)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			UpdateGameStateMainMenu(*(GameStatMainMenuData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::Playing:
		{
			UpdateGameStatePlaying(*(GameStatePlayingData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::GameOver:
		{
			UpdateGameStateGameOver(*(GameStateGameOverData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::Scoreboard:
		{
			UpdateGameStateScoreboard(*(GameStateScoreboardData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::ExitDialog:
		{
			UpdateGameStateExitDialog(*(GameStateExitDialogData*)state.data, game, deltaTime);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			DrawGameStateMainMenu(*(GameStatMainMenuData*)state.data, game, window);
			break;
		}
		case GameStateType::Playing:
		{
			DrawGameStatePlaying(*(GameStatePlayingData*)state.data, game, window);
			break;
		}
		case GameStateType::GameOver:
		{
			DrawGameStateGameOver(*(GameStateGameOverData*)state.data, game, window);
			break;
		}
		case GameStateType::Scoreboard:
		{
			DrawGameStateScoreboard(*(GameStateScoreboardData*)state.data, game, window);
			break;
		}
		case GameStateType::ExitDialog:
		{
			DrawGameStateExitDialog(*(GameStateExitDialogData*)state.data, game, window);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void SortScoreBoard(Game& game)
	{
		// Inserting reversed scoreboard in multimap and back for sortiung
		for (const auto& item : game.scoreboard)
		{
			game.sortedScoreboard.insert({ item.second, item.first });
		}

		game.scoreboard.clear();

		for (const auto& item : game.sortedScoreboard)
		{
			game.scoreboard.insert({ item.second, item.first });
		}

		game.sortedScoreboard.clear();
	}

	void InitGame(Game& game)
	{
		// Init Scoreboard

		game.scoreboard =
		{
			{"Dani", player1Score},
			{"Kristina", player2Score},
			{"Sasha", player3Score},
			{"Player", 0}
		};
		SortScoreBoard(game);

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		SwitchGameState(game, GameStateType::MainMenu);

		game.screenRect = { 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT };
		game.background.setSize(sf::Vector2f(game.screenRect.size.x, game.screenRect.size.y));
		game.background.setFillColor(sf::Color::Black);
		game.background.setPosition(0.f, 0.f);
	}

	void HandleWindowEvents(Game& game, sf::RenderWindow& window)
	{
		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			if (game.gameStateStack.size() > 0)
			{
				HandleWindowEventGameState(game, game.gameStateStack.back(), event);
			}
		}
	}

	
	void DeinitializeGame(Game& game)	
	{
		// Shutdown all game states
		while (game.gameStateStack.size() > 0)
		{
			ShutDownGameState(game, game.gameStateStack.back());
			game.gameStateStack.pop_back();
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
	}
}
