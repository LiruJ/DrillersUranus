#include "MiningMinigame.h"

// Framework includes.
#include <SDL_scancode.h>
#include <SDL_events.h>

// Service includes.
#include "Graphics.h"
#include "Screen.h"

// Data includes.
#include "Game.h"
#include "Rectangle.h"

// Utility includes.
#include "Random.h"
#include "AudioData.h"

/// <summary> Sets up event bindings and the UI. </summary>
void Minigames::MiningMinigame::Initialise()
{
	// Get the events service.
	Events::Events& events = MainGame::Game::GetService().GetEvents();

	// Bind click to handle mining.
	events.AddFrameworkListener(SDL_MOUSEBUTTONDOWN, std::bind(&MiningMinigame::mineAt, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the wall mined event.
	events.AddUserListener(Events::UserEvent::MinedWall, std::bind(&MiningMinigame::mined, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the tool buttons to change the tool.
	events.AddUserListener(Events::UserEvent::ChangeTool, std::bind(&MiningMinigame::changeTool, this, std::placeholders::_1, std::placeholders::_2));
	events.AddFrameworkListener(SDL_KEYDOWN, std::bind(&MiningMinigame::hotkeyTool, this, std::placeholders::_1, std::placeholders::_2));

	// Initialise the GUI.
	m_minigameMenu.Initialise(c_maxTimer);

	// Change the tool to the first one.
	events.PushEvent(Events::UserEvent::ChangeTool, new uint8_t(0), NULL);
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
					// Calculate the window position and draw.
					Point windowPosition = screen.ScreenToWindowSpace(Point(x, y) * SpriteData::c_wallSize);
					graphics.Draw(SpriteData::SheetID::MineWalls, l, Rectangle(windowPosition, screen.ScreenToWindowSize(Point(SpriteData::c_wallSize))));
				}
			}
		}
	}

	// Draw the UI.
	m_minigameMenu.Draw();
}

/// <summary> Prepares the minigame to be played, using the given map wall and prosperity to generate. </summary>
/// <param name="_tilePosition"> The position of the cave wall within the map. </param>
/// <param name="_prosperity"> The prosperity of the wall. </param>
void Minigames::MiningMinigame::Prepare(const Point _tilePosition, const uint8_t _prosperity)
{
	// Start on the first tool.
	MainGame::Game::GetService().GetEvents().PushEvent(Events::UserEvent::ChangeTool, new uint8_t(0), NULL);

	// Set the tile position.
	m_tilePosition = _tilePosition;

	// Generate the wall.
	m_wallData.Generate();

	// Place the gems.
	placeGems(_prosperity);

	// Reset the collapse timer.
	m_collapseTimer = c_maxTimer;
}

/// <summary> Changes the current tool to the given value. </summary>
/// <param name="_toolID"> The new tool ID. </param>
/// <param name="_unused"> Unused. </param>
void Minigames::MiningMinigame::changeTool(void* _toolID, void* _unused = NULL)
{
	// Do nothing if the game state is not minigame.
	if (MainGame::Game::GetGameState() != MainGame::GameState::Minigame) { return; }

	// Set the current tool ID to the given ID.
	m_currentToolID = *static_cast<uint8_t*>(_toolID);
}

/// <summary> Handles the player pressing a key to change tool. </summary>
/// <param name="_scancode"> The scan code of the pressed key. </param>
/// <param name="_mod"> The modifier key that the player was holding on the key press. </param>
void Minigames::MiningMinigame::hotkeyTool(void* _scancode, void* _mod)
{
	// Do nothing if the game state is not minigame.
	if (MainGame::Game::GetGameState() != MainGame::GameState::Minigame) { return; }

	// Cast the scancode.
	SDL_Scancode scancode = *static_cast<SDL_Scancode*>(_scancode);

	// Get the events service.
	Events::Events& events = MainGame::Game::GetService().GetEvents();

	// Cheaper to switch on the given code rather than do any maths with it.
	// Push a change tool event instead of manually changing the tool, so that the function can be reused and anything that's listening for the change tool event can also change.
	switch (scancode)
	{
	case SDL_SCANCODE_1: { events.PushEvent(Events::UserEvent::ChangeTool, new uint8_t(0), NULL); break; }
	case SDL_SCANCODE_2: { events.PushEvent(Events::UserEvent::ChangeTool, new uint8_t(1), NULL); break; }
	case SDL_SCANCODE_3: { events.PushEvent(Events::UserEvent::ChangeTool, new uint8_t(2), NULL); break; }
	}
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

	// Store if a gem was hit.
	bool didHitGem = false;

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
				m_collapseTimer = std::max(0, m_collapseTimer - 15);

				// A gem was hit, so keep track of it.
				didHitGem = true;
			}
			else
			{
				// Subtract any over-damage from the timer, awarding precise hits and punishing hitting the back wall.
				m_collapseTimer = std::max(0, m_collapseTimer - std::max(1, (desiredDamage - damageDealt)));

				// Damage this tile.
				m_wallData.SetValueAt(x, y, m_wallData.GetValueAt(x, y) - damageDealt);

				// Create particles.
				MainGame::Game::GetService().GetParticles().AddParticles(Point(x, y) * SpriteData::c_wallSize, 5, SpriteData::ParticleID::WallStart, SpriteData::ParticleID::WallEnd);
			}
		}
	}

	// Play a sound based on if a gem was hit.
	if(didHitGem) { MainGame::Game::GetService().GetAudio().PlaySound(AudioData::SoundID::HitGem); }
	else { MainGame::Game::GetService().GetAudio().PlayRandomSound(AudioData::VariedSoundID::Smash); }

	// Shake the screen based on how close the wall is to collapsing.
	MainGame::Game::GetService().GetScreen().ShakeScreen((1.0f - ((float_t)m_collapseTimer / c_maxTimer)) * 50);

	// Push the mined event.
	MainGame::Game::GetService().GetEvents().PushEvent(Events::UserEvent::MinedWall, new uint16_t(m_collapseTimer), new uint16_t(c_maxTimer));
}

/// <summary> Fires when the wall is mined. </summary>
/// <param name="_collapseTimer"> The new value of the collapse timer. </param>
/// <param name="_maxTimer"> The max value of the collapse timer. </param>
void Minigames::MiningMinigame::mined(void* _collapseTimer, void* _maxTimer)
{
	// Get the events service.
	Events::Events& events = MainGame::Game::GetService().GetEvents();

	// Remove any uncovered gems and award them to the player.
	std::vector<WallGem>::iterator gemIter = m_wallGems.begin();
	while (gemIter != m_wallGems.end())
	{
		if (gemIter->IsFullyUncovered(m_wallData)) 
		{
			events.PushEvent(Events::UserEvent::MinedGem, new WallGem(*gemIter), NULL);
			MainGame::Game::GetService().GetAudio().PlaySound(AudioData::SoundID::GetGem);
			gemIter = m_wallGems.erase(gemIter);
		}
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

// Initialise the tools.
Minigames::Tool Minigames::MiningMinigame::s_tools[3] = { Minigames::Tool(3, 2), Minigames::Tool(5, 3), Minigames::Tool(11, 7) };