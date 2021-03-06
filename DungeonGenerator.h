#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

// Derived includes.
#include "MapGenerator.h"

// Data includes.
#include "Point.h"
#include "Direction.h"

namespace MapGeneration
{
	/// <summary> Represents a map generator for a dungeon with lots of interconnected rooms. </summary>
	class DungeonGenerator : public MapGeneration::MapGenerator
	{
	public:
		DungeonGenerator() : m_map(NULL) {}

		virtual void Generate(WorldObjects::TileMap&, GameObjects::MapObject&, GameObjects::MapObject&);
	private:
		/// <summary> The amount of rooms to attempt to place. </summary>
		const uint8_t			c_roomAmount = 20;

		/// <summary> The maximum amount of attempts to place a room before giving up. </summary>
		/// <remarks> The higher this value, the more likely all rooms will be placed, lower values will make it more likely for a room to not be placed. </remarks>
		const uint16_t			c_maxRoomAttempts = 300;

		/// <summary> The widest a room can be. </summary>
		const uint8_t			c_maxRoomWidth = 13;

		/// <summary> The least wide a room can be. </summary>
		const uint8_t			c_minRoomWidth = 3;

		/// <summary> The highest a room can be. </summary>
		const uint8_t			c_maxRoomHeight = 9;

		/// <summary> the least high a room can be. </summary>
		const uint8_t			c_minRoomHeight = 3;

		/// <summary> The percentage of corridors to leave when removing dead ends. <c>0</c> for every dead end to be removed, <c>1</c> for none to be removed. </summary>
		/// <remarks> The higher this value, the tighter packed the corridors will be, lower will make the corridors sparser. </remarks>
		const float				c_percentageOfCorridorsToLeave = 0.70f;

		/// <summary> The percentage of the single-thick walls to break down to create alternate ways. <c>0</c> for no broken walls, <c>100</c> for all broken walls. </summary>
		/// <remarks> The higher this value, the more "crazy" the map will appear, with more alternate ways or loops. The lower this value, the more "standard" the map will appear, with long corridors and few alternate paths. </remarks>
		const float				c_percentageOfWallsToBreak = 0.10f;

		/// <summary> The chance for the path to bend left or right. <c>0</c> for 0% chance, <c>100</c> for 100% chance. </summary>
		/// <remarks> The higher this value, the bendier this path will be, and with more dead ends as the paths cross into themselves. The lower this value, the straighter the paths. </remarks>
		const float				c_chanceToBend = 0.55f;

		/// <summary> The amount of prosperity to be added to the map, as an average of all cells. </summary>
		const uint8_t			c_averageProsperityPerCell = 7;

		/// <summary> The tile data that this generator modifies. </summary>
		WorldObjects::TileMap*	m_map;
		
		/// <summary> The amount of corridors on the map. </summary>
		uint32_t				m_corridorAmount = 0;

		void	placeRooms(uint8_t, GameObjects::MapObject&);

		void	generateMaze(GameObjects::MapObject&);

		void	removeDeadEnds(Point);

		void	breakWalls();

		void	generateGems();

		void	visitCell(Point, Direction);

		bool	isCellValidMazeNode(Point);

		int32_t	getAdjacentFloorCellsAmount(Point);

		/// <summary> Checks to see if the cell at the given position has only one directly adjacent open cell. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <param name="_spawn"> The tile position of the spawn. </param>
		/// <returns> <c>true</c> if the cell at the given position has exactly 1 empty side; otherwise, <c>false</c>. </returns>
		bool	isCellDeadEnd(const Point _position, const Point _spawnPosition) { return m_map->IsCellClearAndInRange(_position) && getAdjacentFloorCellsAmount(_position) == 1 && _position != _spawnPosition; }
	};
}
#endif