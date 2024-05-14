#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

namespace ApplesGame
{
	struct Game;

	struct GameStateGameOverData
	{
		// Resources
		sf::Font font;
		sf::SoundBuffer deathBuffer; //going to GameOver
		sf::Sound deathSound; //going to GameOver

		// Data
		float timeSinceGameFinish = 0;

		// UI data
		sf::Text gameOverText;
		sf::Text spaceToRestartText;
		sf::Text scoreboardText;
	};

	void InitGameStateGameOver (GameStateGameOverData& data, Game& game);
	void ShutDownGameStateGameOver(GameStateGameOverData& data, Game& game);
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float deltaTime);
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window);

}