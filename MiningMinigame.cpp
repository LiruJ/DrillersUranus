#include "MiningMinigame.h"

// Graphical includes.
#include "Graphics.h"
#include "Screen.h"

// Utility includes.
#include "Random.h"

// Data includes.
#include "Game.h"
#include "Rectangle.h"

void Minigames::MiningMinigame::Initialise()
{
	// Get the events service.
	Events& events = Game::GetService().GetEvents();

	// Bind click to handle mining.
	events.AddFrameworkListener(SDL_MOUSEBUTTONDOWN, std::bind(&Minigames::MiningMinigame::mineAt, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the tool buttons to change the tool.
	events.AddUserListener(UserEvent::ChangeTool, std::bind(&Minigames::MiningMinigame::changeTool, this, std::placeholders::_1, std::placeholders::_2));

	// Initialise the GUI.
	initialiseGui();
}

void Minigames::MiningMinigame::Draw()
{
	// Get the graphics and screen services.
	Graphics::Graphics& graphics = Game::GetService().GetGraphics();
	Screen& screen = Game::GetService().GetScreen();

	for (int32_t x = 0; x < c_wallWidth; x++)
	{
		for (int32_t y = 0; y < c_wallHeight; y++)
		{
			// Calculate the screen position and draw.
			Point screenPosition = screen.WindowToScreenSpace(Point(x, y) * SpriteData::c_wallSize);
			graphics.Draw(SpriteData::SheetID::MineWalls, m_wallData[x][y], Rectangle(screenPosition, screen.WindowToScreenSize(Point(SpriteData::c_wallSize))));
		}
	}

	// Draw the UI.
	m_bottomBar.Draw();
	m_collapseBar.Draw();
	if (m_currentToolID != 0) { m_toolButtons[0].Draw(); }
	if (m_currentToolID != 1) { m_toolButtons[1].Draw(); }
	if (m_currentToolID != 2) { m_toolButtons[2].Draw(); }
}

void Minigames::MiningMinigame::Generate(const Point _tilePosition, const uint8_t _prosperity)
{
	// Set the tile position.
	m_tilePosition = _tilePosition;

	// Reset the data to the minimum value.
	reset();

	// Create a random number of bumps.
	uint8_t numberOfBumps = Random::RandomBetween(4, 6);
	for (int32_t i = 0; i < numberOfBumps; i++) { generateBump((c_maxHeight - numberOfBumps) + i); }
}

void Minigames::MiningMinigame::changeTool(void * _toolID, void * _unused)
{
	// Do nothing if the game state is not minigame.
	if (Game::GetGameState() != GameState::Minigame) { return; }

	// Set the current tool ID to the given ID.
	m_currentToolID = *static_cast<uint8_t*>(_toolID);
}

void Minigames::MiningMinigame::mineAt(void* _windowX, void* _windowY)
{
	// Do nothing if the game state is not minigame.
	if (Game::GetGameState() != GameState::Minigame) { return; }

	// Get the screen service.
	Screen& screen = Game::GetService().GetScreen();

	// Convert the screen position to a tile position.
	Point tilePosition = screen.ScreenToWindowSpace(Point(*static_cast<int32_t*>(_windowX), *static_cast<int32_t*>(_windowY))) / SpriteData::c_wallSize;

	// If the tile position is not in range, do nothing.
	if (!isInRange(tilePosition)) { return; }

	// Get the size and damage of the current tool.
	uint8_t currentToolSize = s_tools[m_currentToolID].m_size;
	uint8_t currentToolDamage = s_tools[m_currentToolID].m_power;

	// Go over each tile covered by this area, and damage it.
	for (int32_t x = std::max(0, tilePosition.x - (currentToolSize / 2)); x < std::min(c_wallWidth, (uint8_t)( tilePosition.x + (currentToolSize / 2) + 1)); x++)
	{
		for (int32_t y = std::max(0, tilePosition.y - (currentToolSize / 2)); y < std::min(c_wallHeight, (uint8_t)(tilePosition.y + (currentToolSize / 2) + 1)); y++)
		{
			// Get the largest distance from the centre.
			uint8_t largestDistance = std::abs(x - tilePosition.x) + std::abs(y - tilePosition.y);

			// Calculate the damage that should be dealt, and the damage that can be dealt.
			uint8_t desiredDamage = std::max(0, currentToolDamage - largestDistance);
			uint8_t damageDealt = std::min(m_wallData[x][y], desiredDamage);

			// If the desired damage is 0, skip the damage part.
			if (desiredDamage == 0) { continue; }

			// Subtract any over-damage from the timer, awarding precise hits and punishing hitting the back wall.
			m_collapseTimer = std::max(0, m_collapseTimer - std::max(1, (desiredDamage - damageDealt)));

			// Damage this tile.
			m_wallData[x][y] -= damageDealt;
		}
	}

	// Update the collapse timer bar.
	m_collapseBar.SetValue(c_maxTimer - m_collapseTimer);

	// TODO: Check if any gems were uncovered, if so, award them to the player and remove them from the minigame.

	// TODO: Collapse if timer is 0
	if (m_collapseTimer == 0)
	{
		// Get the events service.
		Events& events = Game::GetService().GetEvents();

		// Push the collapse event.
		events.PushEvent(UserEvent::StopMinigame, new Point(m_tilePosition), NULL);
	}
}

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
		m_toolButtons[i].SetEvent(UserEvent::ChangeTool, i);
		m_toolButtons[i].Initialise();
	}
}

void Minigames::MiningMinigame::generateBump(const uint8_t _height)
{
	// Set the current height to the given height.
	uint8_t currentHeight = _height;

	// Much like the cavern generation, start at a random place and randomly move around.
	Point currentPosition(Random::RandomBetween(0, c_wallWidth - 1), Random::RandomBetween(0, c_wallHeight - 1));
	Point nextPosition;
	
	// Every time a placement cannot be made, increment this by 1 to prevent an infnite loop.
	int32_t currentAttempts = 0;

	// Keep going until a certain height is reached.
	while (currentHeight > c_minimumHeight && currentAttempts < c_maxAttempts)
	{
		// Only set the tile if it is lower than the current height, otherwise increment the attempt counter.
		if (m_wallData[currentPosition.x][currentPosition.y] < currentHeight)
		{
			// Set the tile.
			m_wallData[currentPosition.x][currentPosition.y] = currentHeight;

			// Roll to go down one layer and reset the attempt counter.
			if (Random::RandomScalar() < c_downChance && currentHeight > 0) { currentHeight--; currentAttempts = 0; }
		}
		else { currentAttempts++; }

		// Keep going in a random direction until a valid move is found.
		do { nextPosition = currentPosition + Direction::GetRandom().GetNormal(); }
		while (!isInRange(nextPosition));

		// Make the move.
		currentPosition = nextPosition;
	}
}

void Minigames::MiningMinigame::reset()
{
	// Reset the collapse timer and bar.
	m_collapseTimer = c_maxTimer;
	m_collapseBar.SetValue(0);

	for (int32_t x = 0; x < c_wallWidth; x++)
	{
		for (int32_t y = 0; y < c_wallHeight; y++)
		{
			m_wallData[x][y] = c_minimumHeight;
		}
	}
}

// Initialise the tools.
Minigames::Tool Minigames::MiningMinigame::s_tools[3] = { Minigames::Tool(7, 4), Minigames::Tool(11, 7), Minigames::Tool(17, 8) };