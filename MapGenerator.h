#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include "TileMap.h"
#include "MapObject.h"

namespace MapGeneration
{
	class MapGenerator
	{
	public:

		virtual ~MapGenerator() {}

		virtual void Generate(TileMap&, MapObject&, MapObject&) = 0;
	};
}
#endif