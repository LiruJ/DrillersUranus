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

	// Extremely inefficient, but time restrictions prevent me from making any optimised algorithm.
	// If I were to have more time, I would implement a data structure to hold each layer separately.
	for (uint8_t l = 0; l < m_wallData.c_maxValue; l++)
	{
		// Draw all gems on this layer.
		for (uint32_t g = 0; g < m_wallGems.size(); g++) { if (m_wallGems[g].GetLayer() == l) { m_wallGems[g].Draw(); } }

		// Draw rock on this layer.
		for (int32_t x = 0; x < m_wallData.GetWidth(); x++)
		{
			for (int32_t y = 0; y < m_wallData.GetHeight(); y++)
			{
				// If this is the layer to be drawn.
				if (m_wallData.GetValueAt(x, y) == l)
				{
					// Calculate the screen position and draw.
					Point screenPosition = screen.ScreenToWindowSpace(Point(x, y) * SpriteData::c_wallSize);
					graphics.Draw(SpriteData::SheetID::MineWalls, l, Rectangle(screenPosition, screen.ScreenToWindowSize(Point(SpriteData::c_wallSize))));
				}
			}
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

	// Place the gems.
	placeGems(_prosperity);
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

			// Find if a gem was hit. Stupidly inefficient, but the only way to do this without devoting more time to data structures.
			WallGem* hitGem = NULL;
			for (uint32_t g = 0; g < m_wallGems.size(); g++)
			{
				if (m_wallGems[g].GetLayer() > m_wallData.GetValueAt(x, y) && m_wallGems[g].CollidesWith(Point(x, y))) { hitGem = &m_wallGems[g]; break; }
			}

			// If a gem is hit, collapse a certain amount; otherwise, damage the wall.
			if (hitGem != NULL)
			{
				// Subtract a set amount from the timer.
				m_collapseTimer = std::max(0, m_collapseTimer - 10);
			}
			else
			{
				// Subtract any over-damage from the timer, awarding precise hits and punishing hitting the back wall.
				m_collapseTimer = std::max(0, m_collapseTimer - std::max(1, (desiredDamage - damageDealt)));

				// Damage this tile.
				m_wallData.SetValueAt(x, y, m_wallData.GetValueAt(x, y) - damageDealt);
			}
		}
	}

	// Get the events service.
	Events::Events& events = MainGame::Game::GetService().GetEvents();

	// Update the collapse timer bar.
	m_collapseBar.SetValue(c_maxTimer - m_collapseTimer);

	// Remove any uncovered gems and award them to the player.
	std::vector<WallGem>::iterator gemIter = m_wallGems.begin();
	while (gemIter != m_wallGems.end())
	{
		// TODO: Award gems to player.
		if (gemIter->IsFullyUncovered(m_wallData)) { events.PushEvent(Events::UserEvent::MinedGem, new WallGem(*gemIter), NULL); gemIter = m_wallGems.erase(gemIter); }
		else { ++gemIter; }
	}

	// Collapse if collapse timer is 0.
	if (m_collapseTimer == 0) { events.PushEvent(Events::UserEvent::StopMinigame, new Point(m_tilePosition), NULL); }
}

/// <summary> Places gems into the wall based on the given prosperity. </summary>
/// <param name="_prosperity"> A number from <c>0</c> to <c>255</c> for the prosperity of the wall. </param>
void Minigames::MiningMinigame::placeGems(const uint8_t _prosperity)
{
	// Clear the gem list.
	m_wallGems.clear();

	// Start with the given prosperity.
	uint32_t remainingProsperity = (_prosperity + Random::RandomBetween(50, 100)) * 300;

	// Keep placing gems until no prosperity remains.
	while (remainingProsperity > 0)
	{
		// Keep track of the validity of the gem as well as the gem itself.
		WallGem gem(Point(0), 0, SpriteData::GemID::Ruby);
		bool isValid = false;

		// Keep attempting to place a gem until a place is found.
		do
		{
			// Generate a random ID and layer for the gem.
			SpriteData::GemID gemID = (SpriteData::GemID)Random::RandomBetween(0, SpriteData::GemID::Emerald);
			uint8_t layer = Random::RandomBetween(1, m_wallData.c_maxValue);

			// Create the gem.
			gem = WallGem(Point(0), layer, gemID);

			// Create a random position for the gem.
			Point position(Random::RandomBetween(0, m_wallData.GetWidth() - gem.GetWidth()), Random::RandomBetween(0, m_wallData.GetHeight() - gem.GetHeight()));
			gem.SetWallPosition(position);

			// If the gem is uncovered straight away, it is invalid.
			isValid = gem.IsFullyCovered(m_wallData);

			// Only check against other gems if the gem is otherwise valid.
			if (isValid)
			{
				for (uint32_t i = 0; i < m_wallGems.size(); i++)
				{
					// If the gems collide, set it to invalid and break the check loop.
					if (m_wallGems[i].CollidesWith(gem)) { isValid = false; break; }
				}
			}


		} while (!isValid);

		// Add the gem to the vector and reduce the remaining prosperity.
		remainingProsperity = std::max(0, (int32_t)remainingProsperity - gem.GetValue());
		m_wallGems.push_back(gem);
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