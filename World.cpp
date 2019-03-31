#include "World.h"

// Utility includes.
#include "Random.h"

// Service includes.
#include "Events.h"
#include "Controls.h"

// Map generation includes.
#include "CavernGenerator.h"
#include "DungeonGenerator.h"

// Data includes.
#include "Point.h"
#include "Game.h"

void World::Draw()
{
	// Tell the camera to draw.
	m_camera.Draw(*this);
}

int32_t World::Update()
{
	return 0;
}

void World::Initialise()
{
	// Get the event service.
	Events::Events& events = MainGame::Game::GetService().GetEvents();

	// Bind the keydown event.
	events.AddFrameworkListener(SDL_KEYDOWN, std::bind(&World::handleKeyDown, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the minigame stop event.
	events.AddUserListener(Events::UserEvent::StopMinigame, std::bind(&World::stopMinigame, this, std::placeholders::_1, std::placeholders::_2));
}

void World::GenerateRandomMap()
{
	// Initialise the start and end points.
	m_spawnPoint.SetTilePosition(Point(0, 0));
	m_exitPoint.SetTilePosition(Point(0, 0));

	// Generate a random percentage to decide which type of map to generate.
	float mapRoll = Random::RandomScalar();

	// Create an interfaced version of the map generator to use.
	MapGeneration::MapGenerator* mapGenerator = NULL;

	// Use the roll to decide the generator.
	if (mapRoll < 0.5f) { mapGenerator = new MapGeneration::CavernGenerator(); }
	else				{ mapGenerator = new MapGeneration::DungeonGenerator(); }

	// Generate the map then delete the generator, avoid a dangling pointer by setting it to null.
	mapGenerator->Generate(m_tileData, m_spawnPoint, m_exitPoint);
	delete mapGenerator;
	mapGenerator = NULL;

	// Move the player to the spawn.
	m_player.SetTilePosition(m_spawnPoint.GetTilePosition());
}

void World::handleKeyDown(void* _scancode, void* _mod)
{
	// If the game state is not map, do nothing.
	if (MainGame::Game::GetGameState() != MainGame::GameState::Map) { return; }

	// Get the controls service.
	Controls::Controls& controls = MainGame::Game::GetService().GetControls();

	// Cast the scancode and mod.
	SDL_Scancode scancode = *static_cast<SDL_Scancode*>(_scancode);
	uint16_t mod = *static_cast<uint16_t*>(_mod);

	// Get the desired command from the input.
	Controls::Command currentCommand = controls.GetCommandFromKey(scancode);

	// Handle the command.
	switch (currentCommand)
	{
	// Handle the player interacting with the object they're standing on.
	case Controls::Command::Interact:	{ handleInteraction(); break; }

	// If the player swings, handle what they swing at.
	case Controls::Command::Swing:		{ handleSwinging(); break; }

	// Handle movement, if the shift key is held, just face in that direction.
	case Controls::Command::MoveUp:		{ handleMovement(Directions::Up, mod & KMOD_SHIFT); break; }
	case Controls::Command::MoveDown:	{ handleMovement(Directions::Down, mod & KMOD_SHIFT); break; }
	case Controls::Command::MoveLeft:	{ handleMovement(Directions::Left, mod & KMOD_SHIFT); break; }
	case Controls::Command::MoveRight:	{ handleMovement(Directions::Right, mod & KMOD_SHIFT); break; }
	}
}

void World::doTurn()
{
}

void World::handleMovement(const Directions _direction, const bool _noMovement)
{
	// Create a direction object of the wanted move.
	Direction desiredDirection = Direction(_direction);

	// If the cell is clear and movement is wanted, move towards it, otherwise just face towards it.
	if (!_noMovement && m_tileData.CellIsClearAndInRange(m_player.GetTilePosition() + desiredDirection.GetNormal())) { m_player.MoveInDirection(_direction); }
	else { m_player.SetFacing(_direction); }

	// Do a turn since a movement was made.
	doTurn();
}

void World::handleSwinging()
{	
	// Get the position of the cell to be mined.
	Point minePosition = m_player.GetTilePosition() + m_player.GetFacing().GetNormal();

	// If the cell is empty or outside of the playable area, do nothing.
	if (m_tileData.CellIsClear(minePosition) || !m_tileData.CellInPlayableArea(minePosition)) { return; }

	// If the cell has no prosperity, destroy it and do a turn, otherwise put the minigame start event onto the event bus.
	if (m_tileData.GetTileProsperityAt(minePosition) == 0) { m_tileData.FillCellWithRandomFloor(minePosition); doTurn(); }
	else
	{
		// Get the events service then push the event.
		Events::Events& events = MainGame::Game::GetService().GetEvents();
		events.PushEvent(Events::UserEvent::StartMinigame, new Point(minePosition), new uint8_t(m_tileData.GetTileProsperityAt(minePosition)));
	}
}

void World::handleInteraction()
{
	// If the player is standing on the exit point, take them to a new floor.
	if (m_player.GetTilePosition() == m_exitPoint.GetTilePosition()) 
	{
		GenerateRandomMap();
		m_floorCount++;
	}
}

void World::stopMinigame(void* _tilePosition, void* _unused)
{
	// Cast the data.
	Point tilePosition = *static_cast<Point*>(_tilePosition);

	// Since the minigame has ended, the cave wall has collapsed, meaning the wall should be destroyed.
	m_tileData.FillCellWithRandomFloor(tilePosition);
}