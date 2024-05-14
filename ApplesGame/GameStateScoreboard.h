#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <cassert>

namespace ApplesGame
{
	struct Game; 

	struct GameStateScoreboardData
	{
		sf::Font font;
		sf::Text menuScoreboardText;
	};

	void InitGameStateScoreboard(GameStateScoreboardData& data, Game& game);
	void ShutDownGameStateScoreboard(GameStateScoreboardData& data, Game& game);
	void HandleGameStateScoreboardWindowEvent(GameStateScoreboardData& data, Game& game, const sf::Event& event);
	void UpdateGameStateScoreboard(GameStateScoreboardData& data, Game& game, float deltaTime);
	void DrawGameStateScoreboard(GameStateScoreboardData& data, Game& game, sf::RenderWindow& window);
}