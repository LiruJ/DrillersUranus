#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

// Data includes.
#include "TileMap.h"

// Game object includes.
#include "MapObject.h"

namespace MapGeneration
{
	/// <summary> Represents an interfaced version of a map generator that just allows for a map to be generated. </summary>
	class MapGenerator
	{
	public:
		virtual ~MapGenerator() {}

		/// <summary> Generates a map on the given tile map, using the given spawn and exit game objects as part of the map. </summary>
		/// <param name="_map"> The map data. </param>
		/// <param name="_spawn"> The spawn object. </param>
		/// <param name="_exit"> The exit object. </param>
		virtual void Generate(WorldObjects::TileMap& _map, GameObjects::MapObject& _spawn, GameObjects::MapObject& _exit) = 0;
	};
}
#endif