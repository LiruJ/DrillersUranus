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

		virtual void Generate(WorldObjects::TileMap&, MapObject&, MapObject&) = 0;
	};
}
#endif