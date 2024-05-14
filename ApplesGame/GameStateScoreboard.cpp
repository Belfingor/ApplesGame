#include "GameStateScoreboard.h"

namespace ApplesGame
{
	void InitGameStateScoreboard(GameStateScoreboardData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Regular.ttf"));

		data.menuScoreboardText.setFont(data.font);
		data.menuScoreboardText.setCharacterSize(30);
		data.menuScoreboardText.setFillColor(sf::Color::White);
		data.menuScoreboardText.setPosition(10.f, SCREEN_HEIGHT / 2.5f);
		data.menuScoreboardText.setStyle(sf::Text::Bold);
		data.menuScoreboardText.setString("SCOREBOARD: ");


		std::vector<std::pair<std::string, int>> scoreboardItemPairs(game.scoreboard.begin(), game.scoreboard.end());
		std::reverse(scoreboardItemPairs.begin(), scoreboardItemPairs.end());
		for (const auto& item : scoreboardItemPairs)
		{
			data.menuScoreboardText.setString(data.menuScoreboardText.getString() + "\n" + item.first + ":" + std::to_string(item.second));
		}

	}

	void ShutDownGameStateScoreboard(GameStateScoreboardData& data, Game& game)
	{
		// nothing to do here once again
	}

	void HandleGameStateScoreboardWindowEvent(GameStateScoreboardData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PopGameState(game);
			}
		}
	}

	void UpdateGameStateScoreboard(GameStateScoreboardData& data, Game& game, float deltaTime)
	{
		// Nothing to update here
	}

	void DrawGameStateScoreboard(GameStateScoreboardData& data, Game& game, sf::RenderWindow& window)
	{
		window.draw(data.menuScoreboardText);
	}
}