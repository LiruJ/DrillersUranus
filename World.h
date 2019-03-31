#ifndef WORLD_H
#define WORLD_H

// Map object includes.
#include "MapObject.h"
#include "IReadOnlyMapObject.h"
#include "Player.h"

// Graphical includes.
#include "Graphics.h"
#include "Camera.h"
#include "SpriteData.h"

// Data includes.
#include "TileMap.h"
#include "Direction.h"

class World
{
public:
	World() : m_spawnPoint(SpriteData::ObjectID::Spawn), m_exitPoint(SpriteData::ObjectID::Exit), m_tileData(55, 55) {}

	World(World&) = delete;
	World& operator=(const World&) = delete;

	void Initialise();

	void GenerateRandomMap();
	void Draw();
	int32_t Update();

	inline IReadOnlyMapObject& GetPlayer()	{ return m_player; }
	inline IReadOnlyMapObject& GetSpawn()	{ return m_spawnPoint; }
	inline IReadOnlyMapObject& GetExit()	{ return m_exitPoint; }

	// TODO: Replace TileMap object with IReadOnlyTileMap
	inline TileMap& GetTileMap() { return m_tileData; }
private:
	/// <summary> The tile map data. </summary>
	TileMap						m_tileData;

	/// <summary> The player. </summary>
	Player						m_player;

	/// <summary> The entry point of the map. </summary>
	MapObject					m_spawnPoint;

	/// <summary> The exit point of the map. </summary>
	MapObject					m_exitPoint;

	/// <summary> The camera used to render the world. </summary>
	Camera						m_camera;

	/// <summary> The number of floors that the player has explored. </summary>
	uint16_t				m_floorCount = 0;

	/// <summary> How many turns the player can make before they lose. </summary>
	uint16_t				m_turnsUntilCollapse;

	void handleKeyDown(void*, void*);

	void handleMovement(Directions, bool);

	void handleSwinging();

	void handleInteraction();

	void stopMinigame(void*, void*);

	void doTurn();


};

#endif