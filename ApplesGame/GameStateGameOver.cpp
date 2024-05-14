#include "GameStateGameOver.h"
#include <cassert>

namespace ApplesGame 
{
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Regular.ttf"));
		assert(data.deathBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		data.deathSound.setBuffer(data.deathBuffer);
		data.deathSound.setVolume(10.f);
		data.deathSound.play(); //play death sound (might be wrong placement)

		data.timeSinceGameFinish = 0.f;
		game.isGameFinished = true;

		//Init UI
		//"Game Over" Text
		data.gameOverText.setFont(data.font);
		data.gameOverText.setCharacterSize(30);
		data.gameOverText.setFillColor(sf::Color::White);
		data.gameOverText.setPosition(SCREEN_WIDTH / 3.f, SCREEN_HEIGHT / 2.1f);
		data.gameOverText.setStyle(sf::Text::Underlined);
		//Scoreboard Text
		data.scoreboardText.setFont(data.font);
		data.scoreboardText.setCharacterSize(20);
		data.scoreboardText.setFillColor(sf::Color::White);
		data.scoreboardText.setPosition(500.f, 1.f);
		data.scoreboardText.setStyle(sf::Text::Bold);
		//Restart Clue Text
		data.spaceToRestartText.setFont(data.font);
		data.spaceToRestartText.setCharacterSize(30);
		data.spaceToRestartText.setFillColor(sf::Color::White);
		data.spaceToRestartText.setPosition(1.f, 60.f);
		data.spaceToRestartText.setStyle(sf::Text::Bold);
		//Mode Selection Texts
		game.gameMenuTextMode1.setFont(data.font);
		game.gameMenuTextMode1.setCharacterSize(30);
		game.gameMenuTextMode1.setFillColor(sf::Color::White);
		game.gameMenuTextMode1.setPosition(1.f, 1.f);
		game.gameMenuTextMode1.setStyle(sf::Text::Bold);

		game.gameMenuTextMode2.setFont(data.font);
		game.gameMenuTextMode2.setCharacterSize(30);
		game.gameMenuTextMode2.setFillColor(sf::Color::White);
		game.gameMenuTextMode2.setPosition(1.f, 30.f);
		game.gameMenuTextMode2.setStyle(sf::Text::Bold);
	
	}

	void ShutDownGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		// No need to free resources here as will be freed automatically
	}

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				SwitchGameState(game, GameStateType::Playing);
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				//Exit Game Dialog 
				PushGameState(game, GameStateType::ExitDialog, true);
			}
			else if (event.key.code == sf::Keyboard::Num1)
			{
				game.modes = (GameModes)((std::uint8_t)game.modes ^ (std::uint8_t)GameModes::ENDLESS_APPLES_ON);
				if ((std::uint8_t)game.modes & (std::uint8_t)GameModes::ENDLESS_APPLES_ON)
				{
					game.gameMenuTextMode1.setString("Endless Apples (Num1) - ON");
				}
				else
				{
					game.gameMenuTextMode1.setString("Endless Apples (Num1) - OFF");
				}
			}
			else if (event.key.code == sf::Keyboard::Num2)
			{
				game.modes = (GameModes)((std::uint8_t)game.modes ^ (std::uint8_t)GameModes::ACCELERATION_ON);
				if ((std::uint8_t)game.modes & (std::uint8_t)GameModes::ACCELERATION_ON)
				{
					game.gameMenuTextMode2.setString("Acceleration (Num2) - ON");
				}
				else
				{
					game.gameMenuTextMode2.setString("Acceleration (Num2) - OFF");
				}
			}
		}
	}

	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float deltaTime)
	{
		data.timeSinceGameFinish += deltaTime;

		//setting string for scoreboard
		data.scoreboardText.setString("Scoreboard: ");
		
		std::vector<std::pair<std::string, int>> scoreboardItemPairs(game.scoreboard.begin(), game.scoreboard.end());
		std::reverse(scoreboardItemPairs.begin(), scoreboardItemPairs.end());
		for (const auto& item : scoreboardItemPairs)
		{
			data.scoreboardText.setString(data.scoreboardText.getString() + "\n" + item.first + ":" + std::to_string(item.second));
		}
		

		//set game mode string UI according to the mode selected
		if ((std::uint8_t)game.modes & (std::uint8_t)GameModes::ENDLESS_APPLES_ON)
		{
			game.gameMenuTextMode1.setString("Endless Apples (Num1) - ON");
		}
		else
		{
			game.gameMenuTextMode1.setString("Endless Apples (Num1) - OFF");
		}
		if ((std::uint8_t)game.modes & (std::uint8_t)GameModes::ACCELERATION_ON)
		{
			game.gameMenuTextMode2.setString("Acceleration (Num2) - ON");
		}
		else
		{	
			game.gameMenuTextMode2.setString("Acceleration (Num2) - OFF");
		}

		// Setting other texts
		data.spaceToRestartText.setString("Press SPACE to restart");
		data.gameOverText.setString("Game Over! Score: " + std::to_string(game.numEatenApples));

		//Set background colour according to the game mode - green (won) , red (lost)
		if (game.isGameWon)
		{
			game.background.setFillColor(sf::Color::Green);
		}
		else
		{
			game.background.setFillColor(sf::Color::Red);
		}
	}

	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{
		window.draw(data.gameOverText);
		window.draw(game.gameMenuTextMode1); // May not display so have to move texts init to structure in this file
		window.draw(game.gameMenuTextMode2);
		window.draw(data.spaceToRestartText);
		window.draw(data.scoreboardText);
	}
}
