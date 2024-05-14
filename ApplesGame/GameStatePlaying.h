#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Apple.h"
#include "Player.h"
#include "Rock.h"


namespace ApplesGame
{
	struct Game;

	struct GameStatePlayingData
	{
		// Resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Font font;
		sf::SoundBuffer appleBuffer;
		sf::Sound appleSound;

		// Player, apple and rock data
		Player player;
		std::vector<Apple> apples;
		Rock rocks[NUM_ROCKS];
		int numApples = NUM_APPLES_MIN + (rand() % (NUM_APPLES_MAX - NUM_APPLES_MIN));


		// UI Data
		sf::Text scoreCountText;
		sf::Text inputClueText;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutDownGameStatePlaying (GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
}