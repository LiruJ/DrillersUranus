#ifndef WORLD_H
#define WORLD_H

// Data includes.
#include "TileMap.h"
#include "IReadOnlyTileMap.h"
#include "Direction.h"

// Game object includes.
#include "IReadOnlyMapObject.h"
#include "Player.h"
#include "Camera.h"

// Service includes.
#include "Graphics.h"

// Utility includes.
#include "SpriteData.h"

// Typedef includes.
#include <stdint.h>

namespace WorldObjects
{
	/// <summary> Represents the world data and everything in it. </summary>
	class World
	{
	public:
		/// <summary> Create an empty world. </summary>
		World() : m_spawnPoint(SpriteData::ObjectID::Spawn), m_exitPoint(SpriteData::ObjectID::Exit), m_tileData(55, 55) {}

		// Prevent copies.
		World(World&) = delete;
		World& operator=(const World&) = delete;

		void Initialise();

		void Reset();

		void Draw();

		void Update();

		/// <summary> Gets the player. </summary>
		/// <returns> The <see cref="Player"/>. </returns>
		inline GameObjects::Player&					GetPlayer()					{ return m_player; }

		/// <summary> Gets the spawn object. </summary>
		/// <returns> An <see cref="IReadOnlyMapObject"/> form of the spawn. </returns>
		inline GameObjects::IReadOnlyMapObject&		GetSpawn()					{ return m_spawnPoint; }

		/// <summary> Gets the spawn object. </summary>
		/// <returns> An <see cref="IReadOnlyMapObject"/> form of the end. </returns>
		inline GameObjects::IReadOnlyMapObject&		GetExit()					{ return m_exitPoint; }

		/// <summary> Gets a read only version of the <see cref="TileData"/>. </summary>
		/// <returns> A <see cref="IReadOnlyTileMap"/> form of the data. </returns>
		inline IReadOnlyTileMap&					GetTileMap()				{ return m_tileData; }

		/// <summary> Gets the floor the <see cref="Player"/> is on currently. </summary>
		/// <returns> The floor the <see cref="Player"/> is on currently. </returns>
		inline uint16_t								GetCurrentLevel() const		{ return m_floorCount; }

		/// <summary> Gets how many turns until the map starts to collapse. </summary>
		/// <returns> The amount of turns until the map starts to collapse. </returns>
		inline uint16_t								GetCollapseTime() const		{ return m_turnsUntilCollapse; }
	private:
		/// <summary> The most attempts that will be made to collapse a tile. </summary>
		const uint32_t c_maxCollapseAttempts = 5000;

		/// <summary> The tile map data. </summary>
		TileMap					m_tileData;

		/// <summary> The player. </summary>
		GameObjects::Player		m_player;

		/// <summary> The entry point of the map. </summary>
		GameObjects::MapObject	m_spawnPoint;

		/// <summary> The exit point of the map. </summary>
		GameObjects::MapObject	m_exitPoint;

		/// <summary> The camera used to render the world. </summary>
		Camera					m_camera;

		/// <summary> The number of floors that the player has explored. </summary>
		uint16_t				m_floorCount = 0;

		/// <summary> How many turns the player can make before they lose. </summary>
		uint16_t				m_turnsUntilCollapse;

		void generateRandomMap();

		void handleKeyDown(void*, void*);

		void handleMovement(Directions, bool);

		void handleSwinging();

		void handleInteraction();

		void uncoverTiles();

		void stopMinigame(void*, void*);

		void doTurn();

		void collapse();
	};
}
#endif