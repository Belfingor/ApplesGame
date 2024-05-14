#include "GameStateExitDialog.h"
#include "Game.h"
#include <cassert>

namespace ApplesGame
{
	void InitGameStateExitDialog(GameStateExitDialogData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Regular.ttf"));

		data.exitHintText.setFont(data.font);
		data.exitHintText.setCharacterSize(30);
		data.exitHintText.setFillColor(sf::Color::White);
		data.exitHintText.setPosition(10.f, SCREEN_HEIGHT / 2.5f);
		data.exitHintText.setStyle(sf::Text::Bold);
		data.exitHintText.setString("PAUSE \nMain Menu - Enter \nResume - Esc");		
	}
	void ShutDownGameStateExitDialog(GameStateExitDialogData& data, Game& game)
	{
		// nothing to do here once again
	}
	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PopGameState(game);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
	}
	void UpdateGameStateExitDialog(GameStateExitDialogData& data, Game& game, float deltaTime)
	{
		// Have nothing to update here
	}
	void DrawGameStateExitDialog(GameStateExitDialogData& data, Game& game, sf::RenderWindow& window)
	{
		window.draw(data.exitHintText);
	}
}