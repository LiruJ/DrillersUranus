#include "World.h"

// Framework includes.
#include <SDL_events.h>

// Data includes.
#include "Point.h"

// Service includes.
#include "Controls.h"
#include "ParticleManager.h"
#include "Audio.h"
#include "Screen.h"

// Utility includes.
#include "Random.h"
#include "AudioData.h"

// Map generation includes.
#include "CavernGenerator.h"
#include "DungeonGenerator.h"

/// <summary> Draws this <see cref="World"/>. </summary>
/// <param name="_services"> The service provider. </param>
void WorldObjects::World::Draw(Services::ServiceProvider& _services)
{
	// Tell the camera to draw the world.
	m_camera.Draw(*this, _services);
}

/// <summary> Binds this <see cref="World"/> to certain events. </summary>
/// <param name="_events"> The events bus. </param>
void WorldObjects::World::Initialise(Events::Events& _events)
{
	// Bind the keydown event.
	_events.AddFrameworkListener(SDL_KEYDOWN, std::bind(&World::handleKeyDown, this, std::placeholders::_1));

	// Bind the minigame stop event.
	_events.AddUserListener(Events::UserEvent::StopMinigame, std::bind(&World::stopMinigame, this, std::placeholders::_1));

	// Initialise the player.
	m_player.Initialise(_events);

	// Initialise the camera.
	m_camera.Initialise(_events);
}

/// <summary> Resets the world to its starting state. </summary>
void WorldObjects::World::Reset()
{
	m_floorCount = 9;
	m_player.GetInventory().Reset();
	generateRandomMap();
}

/// <summary> Generates a random map and places the player on the spawn. </summary>
void WorldObjects::World::generateRandomMap()
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

	// Set the remaining turns.
	m_turnsUntilCollapse = std::max(ceil((m_tileData.GetWidth() + m_tileData.GetHeight()) * 1.5f), ceil((m_tileData.GetWidth() + m_tileData.GetHeight()) * 3.0f) - (m_floorCount * 5.0f));

	// Uncover the seen tiles.
	uncoverTiles();
}

/// <summary> Handles the player pressing a key to move. </summary>
/// <param name="_context"> The context of the event. </param>
void WorldObjects::World::handleKeyDown(Events::EventContext* _context)
{
	// If the game state is not map, do nothing.
	if (_context->m_gameState != MainGame::GameState::Map) { return; }

	// Cast the scancode and mod.
	SDL_Scancode scancode = *static_cast<SDL_Scancode*>(_context->m_data1);
	uint16_t mod = *static_cast<uint16_t*>(_context->m_data2);

	// Get the desired command from the input.
	Controls::Command currentCommand = _context->m_services->GetService<Controls::Controls>(Services::ServiceType::Controls).GetCommandFromKey(scancode);

	// Handle the command.
	switch (currentCommand)
	{
	// Handle the player interacting with the object they're standing on.
	case Controls::Command::Interact:	{ handleInteraction(*_context->m_services); break; }

	// If the player swings, handle what they swing at.
	case Controls::Command::Swing:		{ handleSwinging(*_context->m_services); break; }

	// Handle movement, if the shift key is held, just face in that direction.
	case Controls::Command::MoveUp:		{ handleMovement(*_context->m_services, Directions::Up, mod & KMOD_SHIFT); break; }
	case Controls::Command::MoveDown:	{ handleMovement(*_context->m_services, Directions::Down, mod & KMOD_SHIFT); break; }
	case Controls::Command::MoveLeft:	{ handleMovement(*_context->m_services, Directions::Left, mod & KMOD_SHIFT); break; }
	case Controls::Command::MoveRight:	{ handleMovement(*_context->m_services, Directions::Right, mod & KMOD_SHIFT); break; }
	}
}

/// <summary> Handle turn-based logic. </summary>
/// <param name="_services"> The service provider. </param>
/// <param name="_amount"> The amount of turns to do, defaults to <c>1</c>. </param>
void WorldObjects::World::doTurn(Services::ServiceProvider& _services, const uint8_t _amount = 1)
{
	// Repeat for the amount of needed turns.
	for (uint8_t i = 0; i < _amount; i++)
	{
		// Decrement the counter.
		m_turnsUntilCollapse = std::max(0, m_turnsUntilCollapse - 1);

		// If the counter is at 0, collapse a bit.
		if (m_turnsUntilCollapse == 0) { collapse(_services); }
	}
}

/// <summary> Causes some tiles to cave in. </summary>
/// <param name="_services"> The service provider. </param>
void WorldObjects::World::collapse(Services::ServiceProvider& _services)
{
	// How many tiles have to be caved in.
	uint8_t tilesToCollapse = Random::RandomBetween(18, 40);

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
			if (position == m_player.GetTilePosition()) 
			{ 
				_services.GetService<Events::Events>(Services::ServiceType::Events).PushEvent(Events::UserEvent::PlayerDied, NULL, NULL);
				_services.GetService<Audio::Audio>(Services::ServiceType::Audio).PlaySound(AudioData::SoundID::PlayerCrushed);
			}
		}
		else { collapseAttempts++; }
	}

	// Play the collapse sound.
	_services.GetService<Audio::Audio>(Services::ServiceType::Audio).PlaySound(AudioData::SoundID::Collapse);

	// Shake the screen a lot.
	_services.GetService<Screens::Screen>(Services::ServiceType::Screen).ShakeScreen(20);
}

/// <summary> Handles player movement. </summary>
/// <param name="_services"> The service provider. </param>
/// <param name="_direction"> The direction in which the player wants to move. </param>
/// <param name="_noMovement"> Is <c>true</c> if the player just wants to face in the direction; otherwise, <c>false</c>. </param>
void WorldObjects::World::handleMovement(Services::ServiceProvider& _services, const Directions _direction, const bool _noMovement)
{
	// Create a direction object of the wanted move.
	Direction desiredDirection = Direction(_direction);

	// If the cell is clear and movement is wanted, move towards it, otherwise just face towards it.
	if (!_noMovement && m_tileData.IsCellClearAndInRange(m_player.GetTilePosition() + desiredDirection.GetNormal())) 
	{
		m_player.MoveInDirection(_direction);
		doTurn(_services);
		_services.GetService<Audio::Audio>(Services::ServiceType::Audio).PlayRandomSound(AudioData::VariedSoundID::Step);
	}
	else { m_player.SetFacing(_direction); }

	// Uncover the seen tiles.
	uncoverTiles();
}

/// <summary> Handles the player swinging their pickaxe to mine the cell in front of them. </summary>
/// <param name="_services"> The service provider. </param>
void WorldObjects::World::handleSwinging(Services::ServiceProvider& _services)
{	
	// Get the position of the cell to be mined.
	Point minePosition = m_player.GetTilePosition() + m_player.GetFacing().GetNormal();

	// If the cell is empty or outside of the playable area, do nothing.
	if (!m_tileData.IsCellInPlayableArea(minePosition) || m_tileData.IsCellClear(minePosition)) { return; }

	// If the cell has no prosperity, destroy it and do a turn, otherwise put the minigame start event onto the event bus.
	if (m_tileData.GetTileAt(minePosition).m_prosperity == 0) 
	{
		m_tileData.FillCellWithRandomFloor(minePosition); 
		doTurn(_services, 2);

		// Play the sound.
		_services.GetService<Audio::Audio>(Services::ServiceType::Audio).PlayRandomSound(AudioData::VariedSoundID::Hit);

		// Create particles.
		_services.GetService<Particles::ParticleManager>(Services::ServiceType::Particles).AddParticles(minePosition * SpriteData::c_tileSize, 50, SpriteData::ParticleID::WallStart, SpriteData::ParticleID::WallEnd);

		// Shake the screen a bit.
		_services.GetService<Screens::Screen>(Services::ServiceType::Screen).ShakeScreen(4);
	}
	else
	{
		// Push the event to start the minigame.
		_services.GetService<Events::Events>(Services::ServiceType::Events).PushEvent(Events::UserEvent::StartMinigame, new Point(minePosition), new uint8_t(m_tileData.GetTileAt(minePosition).m_prosperity));
	}

	// Uncover the seen tiles.
	uncoverTiles();
}

/// <summary> Handles the player interacting with the object on which they are standing. </summary>
/// <param name="_services"> The service provider. </param>
void WorldObjects::World::handleInteraction(Services::ServiceProvider& _services)
{
	// If the player is standing on the exit point, take them to a new floor.
	if (m_player.GetTilePosition() == m_exitPoint.GetTilePosition()) { handleNewFloor(_services); }
}

/// <summary> Handles the player going down a floor. </summary>
/// <param name="_services"> The service provider. </param>
void WorldObjects::World::handleNewFloor(Services::ServiceProvider& _services)
{
	// Play the exit sound.
	_services.GetService<Audio::Audio>(Services::ServiceType::Audio).PlaySound(AudioData::SoundID::UseExit);

	// If the floor will be less than 10, continue on as normal; otherwise, win the game.
	if (++m_floorCount < 10) { generateRandomMap(); }
	else
	{
		// Play the sound for the player winning, and push the won event.
		_services.GetService<Events::Events>(Services::ServiceType::Events).PushEvent(Events::UserEvent::PlayerWon, NULL, NULL);
		_services.GetService<Audio::Audio>(Services::ServiceType::Audio).PlaySound(AudioData::SoundID::Win);
	}
}

/// <summary> Discovers tiles in front of the player. </summary>
void WorldObjects::World::uncoverTiles()
{
	// Get the start of the end points.
	Point startPosition = (m_player.GetTilePosition() + (m_player.GetFacing().GetNormal() * m_player.GetSightDistance())) + (m_player.GetFacing().GetLeft().GetNormal() * m_player.GetSightDistance());

	// Get the player's central position.
	Vector2 playerPosition = Vector2(m_player.GetTilePosition().x + 0.5f, m_player.GetTilePosition().y + 0.5f);

	// Repeat for all the end points.
	for (uint8_t x = 0; x < 1 + m_player.GetSightDistance() * 2; x++)
	{
		// Calculate the end point of the line.
		Point endPoint = startPosition + (m_player.GetFacing().GetRight().GetNormal() * x);

		// Get the cells covered by the line.
		std::vector<Point> lineOfSight = Point::getCoveredPoints(playerPosition, Vector2(endPoint.x + 0.5f, endPoint.y + 0.5f));

		for (uint16_t p = 0; p < lineOfSight.size(); p++)
		{
			// Uncover the tile.
			m_tileData.SetCellVisiblity(lineOfSight[p], true);

			// If this cell blocks vision, break the line.
			if (!m_tileData.IsCellClearAndInRange(lineOfSight[p])) { break; }
		}
	}
}

/// <summary> Handles breaking the gem wall after the player has finished mining it. </summary>
/// <param name="_context"> The context of the event. </param>
void WorldObjects::World::stopMinigame(Events::EventContext* _context)
{
	// Cast the data.
	Point tilePosition = *static_cast<Point*>(_context->m_data1);

	// Since the minigame has ended, the cave wall has collapsed, meaning the wall should be destroyed.
	m_tileData.FillCellWithRandomFloor(tilePosition);

	// Play the gem wall collapse sound.
	_context->m_services->GetService<Audio::Audio>(Services::ServiceType::Audio).PlaySound(AudioData::SoundID::GemWallCollapse);

	// Create particles.
	_context->m_services->GetService<Particles::ParticleManager>(Services::ServiceType::Particles).AddParticles(tilePosition * SpriteData::c_tileSize, 50, SpriteData::ParticleID::WallStart, SpriteData::ParticleID::WallEnd);

	// Do turns.
	doTurn(*_context->m_services, 10);

	// Uncover the seen tiles.
	uncoverTiles();
}