#include "GameStatePlaying.h"
#include "Game.h"
#include <cassert>

namespace ApplesGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		assert(data.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(data.rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(data.appleBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		data.appleSound.setBuffer(data.appleBuffer);
		data.appleSound.setVolume(10.f);
		assert(data.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Regular.ttf"));

		// Init Background Settings
		game.background.setFillColor(sf::Color::Black);

		// Generate random number of apples and create a pointer for Apple array 
		data.apples.resize(data.numApples);

		// Init Player
		InitPlayer(data.player, data.playerTexture);

		// Init Apples
		for (Apple& apple : data.apples)
		{
			SetApplePosition(apple, GetRandomPostionInRectangle(game.screenRect));
			InitApple(apple, data.appleTexture);
		}
	

		// Init Rocks
		for (int i = 0; i < NUM_ROCKS; ++i) 
		{
			InitRock(data.rocks[i], data.rockTexture);
		}
		// Set Rocks Position
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			SetRockPosition(data.rocks[i], GetRandomPostionInRectangle(game.screenRect));
		}

		game.numEatenApples = 0;
		game.isGameFinished = false;
		game.isGameWon = false;

		data.scoreCountText.setFont(data.font);
		data.scoreCountText.setCharacterSize(24);
		data.scoreCountText.setFillColor(sf::Color::White);
		data.scoreCountText.setPosition(10.f, 10.f);

		data.inputClueText.setFont(data.font);
		data.inputClueText.setCharacterSize(24);
		data.inputClueText.setFillColor(sf::Color::White);
		data.inputClueText.setPosition(SCREEN_WIDTH / 1.6f, 10.f);
		data.inputClueText.setString("Arrows to move, Esc to exit");


	}
	void ShutDownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		data.apples.clear();
		// No need to free other resources here as will be freed automatically
	}
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::ExitDialog, false);
			}
		}
	}
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime)
	{
		// Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			SetPlayerDirection(data.player, PlayerDirection::Right);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			SetPlayerDirection(data.player, PlayerDirection::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			SetPlayerDirection(data.player, PlayerDirection::Left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			SetPlayerDirection(data.player, PlayerDirection::Down);
		}

		UpdatePlayer(data.player, deltaTime);

		// Find player collisions with apples
		for (Apple& apple : data.apples)
		{
			if (DoShapesCollide(GetPlayerCollider(data.player), GetAppleCollider(apple)))
			{
				//condition for endless apples mode 
				if ((std::uint8_t)game.modes & (std::uint8_t)GameModes::ENDLESS_APPLES_ON)
				{
					SetApplePosition(apple, GetRandomPostionInRectangle(game.screenRect));
				}
				//condition for NON-endless apples mode 
				else
				{
					MarkAppleAsEaten(apple);
					if (data.numApples == game.numEatenApples + 1) //needs +1 as it will reg AFTER last eaten apple 
					{
						game.isGameWon = true;
						PushGameState(game, GameStateType::GameOver, false);
					}

				}

				//condition for mode WITH acceleration
				if ((std::uint8_t)game.modes & (std::uint8_t)GameModes::ACCELERATION_ON)
				{
					SetPlayerSpeed(data.player, GetPlayerSpeed(data.player) + ACCELERATION);
				}
				//condition for mode WITHOUT acceleration
				else
				{
					SetPlayerSpeed(data.player, GetPlayerSpeed(data.player));
				}

				++game.numEatenApples;
				data.appleSound.play();
			}
		}
		// Set currenyly updated score
		data.scoreCountText.setString("Apple score: " + std::to_string(game.numEatenApples));

		// Identify player's score on the scoreboard and 
		game.scoreboard["Player"] = std::max(game.scoreboard["Player"], game.numEatenApples);
		SortScoreBoard(game);


		// Find player collisions with rocks
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			if (DoShapesCollide(GetPlayerCollider(data.player), GetRockCollider(data.rocks[i])))
			{
				PushGameState(game, GameStateType::GameOver, false);
			}
		}

		// Check screen borders collision
		if (!DoShapesCollide(GetPlayerCollider(data.player), game.screenRect))
		{
			PushGameState(game, GameStateType::GameOver, false);
		}
	}
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		//Draw background
		window.draw(game.background);
		//Draw Player
		DrawPlayer(data.player, window);

		//Draw Apples
		for (Apple& apple : data.apples)
		{
			DrawApple(apple, window);
		}
		//Draw Rocks
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			DrawRock(data.rocks[i], window);
		}

		//Draw UI
		if (!game.isGameFinished)
		{
			window.draw(data.scoreCountText);
			window.draw(data.inputClueText);	
		}

	}
}