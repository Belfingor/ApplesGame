#include "GameStateMainMenu.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
	void InitGameStateMainMenu(GameStatMainMenuData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.menu.rootItem.hintText.setString("Apples Game");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(48);
		data.menu.rootItem.hintText.setFillColor(sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.startGameItem);
		data.menu.rootItem.children.push_back(&data.scoreboardItem);
		data.menu.rootItem.children.push_back(&data.optionsItem);
		data.menu.rootItem.children.push_back(&data.exitGameItem);

		data.startGameItem.text.setString("Start Game");
		data.startGameItem.text.setFont(data.font);
		data.startGameItem.text.setCharacterSize(24);

		data.scoreboardItem.text.setString("Scoreboard");
		data.scoreboardItem.text.setFont(data.font);
		data.scoreboardItem.text.setCharacterSize(24);

		data.optionsItem.text.setString("Options");
		data.optionsItem.text.setFont(data.font);
		data.optionsItem.text.setCharacterSize(24);
		data.optionsItem.hintText.setString("Options");
		data.optionsItem.hintText.setFont(data.font);
		data.optionsItem.hintText.setCharacterSize(48);
		data.optionsItem.hintText.setFillColor(sf::Color::Red);
		data.optionsItem.childrenOrientation = Orientation::Vertical;
		data.optionsItem.childrenAlignment = Alignment::Middle;
		data.optionsItem.childrenSpacing = 10.f;
		data.optionsItem.children.push_back(&data.optionsEndlessApplesItem);
		data.optionsItem.children.push_back(&data.optionsAccelerationOnItem);

		data.optionsEndlessApplesItem.text.setString("Infinite Apples: On/Off");
		data.optionsEndlessApplesItem.text.setFont(data.font);
		data.optionsEndlessApplesItem.text.setCharacterSize(24);

		data.optionsAccelerationOnItem.text.setString("With Acceleration: On/Off");
		data.optionsAccelerationOnItem.text.setFont(data.font);
		data.optionsAccelerationOnItem.text.setCharacterSize(24);

		data.exitGameItem.text.setString("Exit Game");
		data.exitGameItem.text.setFont(data.font);
		data.exitGameItem.text.setCharacterSize(24);
		data.exitGameItem.hintText.setString("Are you sure?");
		data.exitGameItem.hintText.setFont(data.font);
		data.exitGameItem.hintText.setCharacterSize(48);
		data.exitGameItem.hintText.setFillColor(sf::Color::Red);
		data.exitGameItem.childrenOrientation = Orientation::Vertical;
		data.exitGameItem.childrenAlignment = Alignment::Middle;
		data.exitGameItem.childrenSpacing = 10.f;
		data.exitGameItem.children.push_back(&data.yesItem);
		data.exitGameItem.children.push_back(&data.noItem);

		data.yesItem.text.setString("Yes");
		data.yesItem.text.setFont(data.font);
		data.yesItem.text.setCharacterSize(24);

		data.noItem.text.setString("No");
		data.noItem.text.setFont(data.font);
		data.noItem.text.setCharacterSize(24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.startGameItem);
	}
	void ShutDownGameStateMainMenu(GameStatMainMenuData& data, Game& game)
	{
		// Nothing to do here (memory will be freed automatically)
	}
	void HandleGameStateMainMenuWindowEvent(GameStatMainMenuData& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selectedItem == &data.startGameItem)
				{
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.scoreboardItem)
				{
					PushGameState(game, GameStateType::Scoreboard, true);
				}
				else if (data.menu.selectedItem == &data.optionsItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.optionsEndlessApplesItem)
				{
					game.modes = (GameModes)((std::uint8_t)game.modes ^ (std::uint8_t)GameModes::ENDLESS_APPLES_ON);
				}
				else if (data.menu.selectedItem == &data.optionsAccelerationOnItem)
				{
					game.modes = (GameModes)((std::uint8_t)game.modes ^ (std::uint8_t)GameModes::ACCELERATION_ON);
				}
				else if (data.menu.selectedItem == &data.exitGameItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					SwitchGameState(game, GameStateType::None);
				}
				else if (data.menu.selectedItem == &data.noItem)
				{
					CollapseSelectedItem(data.menu);
				}
				else
				{
					ExpandSelectedItem(data.menu);
				}
			}

			Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				SelectPreviousMenuItem(data.menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				SelectNextMenuItem(data.menu);
			}
		}
	}
	void UpdateGameStateMainMenu(GameStatMainMenuData& data, Game& game, float deltaTime)
	{
		if ((std::uint8_t)game.modes & (std::uint8_t)GameModes::ENDLESS_APPLES_ON)
		{
			data.optionsEndlessApplesItem.text.setString("Endless Apples - ON");
		}
		else
		{
			data.optionsEndlessApplesItem.text.setString("Endless Apples - OFF");
		}
		if ((std::uint8_t)game.modes & (std::uint8_t)GameModes::ACCELERATION_ON)
		{
			data.optionsAccelerationOnItem.text.setString("Acceleration - ON");
		}
		else
		{
			data.optionsAccelerationOnItem.text.setString("Acceleration - OFF");
		}
	}
	void DrawGameStateMainMenu(GameStatMainMenuData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, {0.5f, 0.f});
	}
}