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

/// <summary> Draws this <see cref="World"/>. </summary>
void WorldObjects::World::Draw()
{
	// Tell the camera to draw the world.
	m_camera.Draw(*this);
}

/// <summary> Updates this <see cref="World"/>. </summary>
void WorldObjects::World::Update()
{

}

/// <summary> Binds this <see cref="World"/> to certain events. </summary>
void WorldObjects::World::Initialise()
{
	// Get the event service.
	Events::Events& events = MainGame::Game::GetService().GetEvents();

	// Bind the keydown event.
	events.AddFrameworkListener(SDL_KEYDOWN, std::bind(&World::handleKeyDown, this, std::placeholders::_1, std::placeholders::_2));

	// Bind the minigame stop event.
	events.AddUserListener(Events::UserEvent::StopMinigame, std::bind(&World::stopMinigame, this, std::placeholders::_1, std::placeholders::_2));

	// Initialise the player.
	m_player.Initialise();
}

/// <summary> Generates a random map and places the player on the spawn. </summary>
void WorldObjects::World::GenerateRandomMap()
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

	// Set the remaining turns based on how far away the exit is.
	uint32_t distance = abs(m_spawnPoint.GetTilePosition().x - m_exitPoint.GetTilePosition().x) + abs(m_spawnPoint.GetTilePosition().y - m_exitPoint.GetTilePosition().y);
	m_turnsUntilCollapse = ceil(distance * (2.0f + Random::RandomScalar())) - (m_floorCount * Random::RandomBetween(1, 6));
}

/// <summary> Handles the player pressing a key to move/ </summary>
/// <param name="_scancode"> The scan code of the pressed key. </param>
/// <param name="_mod"> The modifier key that the player was holding on the key press. </param>
void WorldObjects::World::handleKeyDown(void* _scancode, void* _mod)
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

/// <summary> Handle turn-based logic. </summary>
void WorldObjects::World::doTurn()
{
	// Decrement the counter.
	m_turnsUntilCollapse = std::max(0, m_turnsUntilCollapse - 1);

	// If the counter is at 0, collapse a bit.
	if (m_turnsUntilCollapse == 0) { collapse(); }
}

/// <summary> Causes some tiles to cave in. </summary>
void WorldObjects::World::collapse()
{
	// How many tiles have to be caved in.
	uint8_t tilesToCollapse = Random::RandomBetween(12, 30);

	// How many attempts to cave a tile in have been made.
	uint32_t collapseAttempts = 0;

	// Keep caving in tiles until the limit is reached or no more attempts can be made.
	while (collapseAttempts < c_maxCollapseAttempts && tilesToCollapse > 0)
	{
		// Generate a random position.
		Point position(Random::RandomBetween(1, m_tileData.GetWidth() - 2), Random::RandomBetween(1, m_tileData.GetHeight() - 2));

		// If this cell is valid to collapse, collapse it; otherwise, mark it as an attempt.
		if (m_tileData.IsCellClear(position) && m_spawnPoint.GetTilePosition() != position && m_exitPoint.GetTilePosition() != position) 
		{ 
			m_tileData.FillCellWithRandomWall(position);
			--tilesToCollapse;
			collapseAttempts = 0;

			// If the player was crushed by this tile, send the end game event.
			if (position == m_player.GetTilePosition()) { MainGame::Game::GetService().GetEvents().PushEvent(Events::UserEvent::PlayerDied, NULL, NULL); }
		}
		else { ++collapseAttempts; }
	}

}

/// <summary> Handles player movement. </summary>
/// <param name="_direction"> The direction in which the player wants to move. </param>
/// <param name="_noMovement"> Is <c>true</c> if the player just wants to face in the direction; otherwise, <c>false</c>. </param>
void WorldObjects::World::handleMovement(const Directions _direction, const bool _noMovement)
{
	// Create a direction object of the wanted move.
	Direction desiredDirection = Direction(_direction);

	// If the cell is clear and movement is wanted, move towards it, otherwise just face towards it.
	if (!_noMovement && m_tileData.IsCellClearAndInRange(m_player.GetTilePosition() + desiredDirection.GetNormal())) { m_player.MoveInDirection(_direction); doTurn(); }
	else { m_player.SetFacing(_direction); }
}

/// <summary> Handles the player swinging their pickaxe to mine the cell in front of them. </summary>
void WorldObjects::World::handleSwinging()
{	
	// Get the position of the cell to be mined.
	Point minePosition = m_player.GetTilePosition() + m_player.GetFacing().GetNormal();

	// If the cell is empty or outside of the playable area, do nothing.
	if (m_tileData.IsCellClear(minePosition) || !m_tileData.IsCellInPlayableArea(minePosition)) { return; }

	// If the cell has no prosperity, destroy it and do a turn, otherwise put the minigame start event onto the event bus.
	if (m_tileData.GetTileAt(minePosition).m_prosperity == 0) { m_tileData.FillCellWithRandomFloor(minePosition); doTurn(); }
	else
	{
		// Get the events service then push the event.
		Events::Events& events = MainGame::Game::GetService().GetEvents();
		events.PushEvent(Events::UserEvent::StartMinigame, new Point(minePosition), new uint8_t(m_tileData.GetTileAt(minePosition).m_prosperity));
	}
}

/// <summary> Handles the player interacting with the object on which they are standing. </summary>
void WorldObjects::World::handleInteraction()
{
	// If the player is standing on the exit point, take them to a new floor.
	if (m_player.GetTilePosition() == m_exitPoint.GetTilePosition()) 
	{
		GenerateRandomMap();
		m_floorCount++;
	}
}

/// <summary> Handles breaking the gem wall after the player has finished mining it. </summary>
/// <param name="_tilePosition"> The position of the tile. </param>
/// <param name="_unused"> Unused. </param>
void WorldObjects::World::stopMinigame(void* _tilePosition, void* _unused)
{
	// Cast the data.
	Point tilePosition = *static_cast<Point*>(_tilePosition);

	// Since the minigame has ended, the cave wall has collapsed, meaning the wall should be destroyed.
	m_tileData.FillCellWithRandomFloor(tilePosition);

	// Do a turn.
	doTurn();
}