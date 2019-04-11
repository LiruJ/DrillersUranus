#include "MiningMinigame.h"

// Service includes.
#include "Graphics.h"
#include "Screen.h"

// Data includes.
#include "Game.h"
#include "Rectangle.h"

// Utility includes.
#include "Random.h"

/// <summary> Sets up event bindings and the UI. </summary>
void Minigames::MiningMinigame::Initialise()
{
	// Get the events service.
	Events::Events& events = MainGame::Game::GetService().GetEvents();

	// Bind click to handle mining.
	events.AddFrameworkListener(SDL_MOUSEBUTTONDOWN, std::bind(&Minigames::MiningMinigame::mineAt, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the tool buttons to change the tool.
	events.AddUserListener(Events::UserEvent::ChangeTool, std::bind(&Minigames::MiningMinigame::changeTool, this, std::placeholders::_1, std::placeholders::_2));

	// Initialise the GUI.
	initialiseGui();
}

/// <summary> Draws the minigame and the UI. </summary>
void Minigames::MiningMinigame::Draw()
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = MainGame::Game::GetService().GetGraphics();
	Screens::Screen& screen = MainGame::Game::GetService().GetScreen();

	for (int32_t x = 0; x < m_wallData.GetWidth(); x++)
	{
		for (int32_t y = 0; y < m_wallData.GetHeight(); y++)
		{
			// Calculate the screen position and draw.
			Point screenPosition = screen.ScreenToWindowSpace(Point(x, y) * SpriteData::c_wallSize);
			graphics.Draw(SpriteData::SheetID::MineWalls, m_wallData.GetValueAt(x, y), Rectangle(screenPosition, screen.ScreenToWindowSize(Point(SpriteData::c_wallSize))));
		}
	}

	// Draw the UI.
	m_bottomBar.Draw();
	m_collapseBar.Draw();
	if (m_currentToolID != 0) { m_toolButtons[0].Draw(); }
	if (m_currentToolID != 1) { m_toolButtons[1].Draw(); }
	if (m_currentToolID != 2) { m_toolButtons[2].Draw(); }
}

/// <summary> Prepares the minigame to be played, using the given map wall and prosperity to generate. </summary>
/// <param name="_tilePosition"> The position of the cave wall within the map. </param>
/// <param name="_prosperity"> The prosperity of the wall. </param>
void Minigames::MiningMinigame::Prepare(const Point _tilePosition, const uint8_t _prosperity)
{
	// Reset the collapse timer and bar.
	m_collapseTimer = c_maxTimer;
	m_collapseBar.SetValue(0);

	// Set the tile position.
	m_tilePosition = _tilePosition;

	// Generate the wall.
	m_wallData.Generate();
}

/// <summary> Changes the current tool to the given value. </summary>
/// <param name="_toolID"> The new tool ID. </param>
/// <param name="_unused"> Unused. </param>
void Minigames::MiningMinigame::changeTool(void * _toolID, void * _unused)
{
	// Do nothing if the game state is not minigame.
	if (MainGame::Game::GetGameState() != MainGame::GameState::Minigame) { return; }

	// Set the current tool ID to the given ID.
	m_currentToolID = *static_cast<uint8_t*>(_toolID);
}

/// <summary> Handles the player clicking on the wall to mine. </summary>
/// <param name="_windowX"> The x position of the click. </param>
/// <param name="_windowY"> The y position of the click. </param>
void Minigames::MiningMinigame::mineAt(void* _windowX, void* _windowY)
{
	// Do nothing if the game state is not minigame.
	if (MainGame::Game::GetGameState() != MainGame::GameState::Minigame) { return; }

	// Get the screen service.
	Screens::Screen& screen = MainGame::Game::GetService().GetScreen();

	// Convert the screen position to a tile position.
	Point tilePosition = screen.WindowToScreenSpace(Point(*static_cast<int32_t*>(_windowX), *static_cast<int32_t*>(_windowY))) / SpriteData::c_wallSize;

	// If the tile position is not in range, do nothing.
	if (!m_wallData.IsInRange(tilePosition)) { return; }

	// Get the size and damage of the current tool.
	uint8_t currentToolSize = s_tools[m_currentToolID].m_size;
	uint8_t currentToolDamage = s_tools[m_currentToolID].m_power;

	// Go over each tile covered by this area, and damage it.
	for (int32_t x = std::max(0, tilePosition.x - (currentToolSize / 2)); x < std::min(m_wallData.GetWidth(), (uint8_t)( tilePosition.x + (currentToolSize / 2) + 1)); x++)
	{
		for (int32_t y = std::max(0, tilePosition.y - (currentToolSize / 2)); y < std::min(m_wallData.GetHeight(), (uint8_t)(tilePosition.y + (currentToolSize / 2) + 1)); y++)
		{
			// Get the largest distance from the centre.
			uint8_t largestDistance = std::abs(x - tilePosition.x) + std::abs(y - tilePosition.y);

			// Calculate the damage that should be dealt, and the damage that can be dealt.
			uint8_t desiredDamage = std::max(0, currentToolDamage - largestDistance);
			uint8_t damageDealt = std::min(m_wallData.GetValueAt(x, y), desiredDamage);

			// If the desired damage is 0, skip the damage part.
			if (desiredDamage == 0) { continue; }

			// Subtract any over-damage from the timer, awarding precise hits and punishing hitting the back wall.
			m_collapseTimer = std::max(0, m_collapseTimer - std::max(1, (desiredDamage - damageDealt)));

			// Damage this tile.
			m_wallData.SetValueAt(x, y, m_wallData.GetValueAt(x, y) - damageDealt);
		}
	}

	// Update the collapse timer bar.
	m_collapseBar.SetValue(c_maxTimer - m_collapseTimer);

	// TODO: Check if any gems were uncovered, if so, award them to the player and remove them from the minigame.

	// TODO: Collapse if timer is 0
	if (m_collapseTimer == 0)
	{
		// Get the events service.
		Events::Events& events = MainGame::Game::GetService().GetEvents();

		// Push the collapse event.
		events.PushEvent(Events::UserEvent::StopMinigame, new Point(m_tilePosition), NULL);
	}
}

/// <summary> Sets up the GUI. </summary>
void Minigames::MiningMinigame::initialiseGui()
{
	// Initialise the background UI.
	m_bottomBar = UserInterface::Frame(Point(0, 480), Point(960, 60), SpriteData::UIID::MinigameBar);

	// Initialise the collapse bar.
	m_collapseBar = UserInterface::ProgressBar(Point(0, 512), Point(960, 28), SpriteData::UIID::WallTimer);
	m_collapseBar.SetMax(c_maxTimer);
	m_collapseBar.SetValue(0);

	// Initialise the buttons.
	for (int32_t i = 0; i < 3; i++)
	{
		m_toolButtons[i] = UserInterface::Button(Point(i * 32, 480), Point(32, 32), SpriteData::UIID::Pickaxe + i);
		m_toolButtons[i].SetEvent(Events::UserEvent::ChangeTool, i);
		m_toolButtons[i].Initialise();
	}
}

// Initialise the tools.
Minigames::Tool Minigames::MiningMinigame::s_tools[3] = { Minigames::Tool(7, 4), Minigames::Tool(11, 7), Minigames::Tool(17, 8) };