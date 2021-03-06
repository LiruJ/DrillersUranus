#ifndef CAVERNGENERATOR_H
#define CAVERNGENERATOR_H

// Derived includes.
#include "MapGenerator.h"

namespace MapGeneration
{
	/// <summary> Represents a generator for a big hollow cavern. </summary>
	class CavernGenerator : public MapGeneration::MapGenerator
	{
	public:
		CavernGenerator() {}

		virtual void Generate(WorldObjects::TileMap&, GameObjects::MapObject&, GameObjects::MapObject&);
	private:
		/// <summary> The min percentage of all tiles on the map to turn into floors. <c>0</c> for none, <c>100</c> for all. </summary>
		float				c_minPercentageOfMapToCarve = 0.5f;

		/// <summary> The max percentage of all tiles on the map to turn into floors. <c>0</c> for none, <c>100</c> for all. </summary>
		float				c_maxPercentageOfMapToCarve = 0.8f;

		/// <summary> The amount of prosperity to be added to the map, as an average of all cells. </summary>
		const uint8_t		c_averageProsperityPerCell = 5;

		/// <summary> The chance for each step to go closer towards the centre. <c>0</c> for no weighting, <c>100</c> for full weighting. </summary>
		const float			c_centreWeight = 0.1f;

		void generateGems(WorldObjects::TileMap&);
	};
}
#endif