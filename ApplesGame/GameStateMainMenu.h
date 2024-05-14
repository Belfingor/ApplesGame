#pragma once
#include "SFML/Graphics.hpp"
#include "MainMenu.h"

namespace ApplesGame
{
	struct Game;

	struct GameStatMainMenuData
	{
		sf::Font font;

		MenuItem startGameItem;
		MenuItem scoreboardItem;
		MenuItem optionsItem;
		MenuItem optionsEndlessApplesItem;
		MenuItem optionsAccelerationOnItem;
		MenuItem exitGameItem;
		MenuItem yesItem;
		MenuItem noItem;
		Menu menu;
	};

	void InitGameStateMainMenu (GameStatMainMenuData& data, Game& game);
	void ShutDownGameStateMainMenu (GameStatMainMenuData& data, Game& game);
	void HandleGameStateMainMenuWindowEvent(GameStatMainMenuData& data, Game& game, const sf::Event& event);
	void UpdateGameStateMainMenu(GameStatMainMenuData& data, Game& game, float deltaTime);
	void DrawGameStateMainMenu(GameStatMainMenuData& data, Game& game, sf::RenderWindow& window);
}