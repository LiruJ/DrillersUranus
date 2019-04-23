#ifndef PLAYER_H
#define PLAYER_H

// Derived includes.
#include "MapObject.h"

// Service includes.
#include "Events.h"
#include "EventContext.h"

// Data includes.
#include "Direction.h"
#include "Inventory.h"

namespace GameObjects
{
	/// <summary> Represents the player on the map. </summary>
	class Player : public MapObject
	{
	public:
		/// <summary> Creates a basic <see cref="Player"/>. </summary>
		Player() : MapObject::MapObject(SpriteData::ObjectID::PlayerUp), m_sightDistance(4), m_facing(Direction(Directions::Up)) {}

		void Initialise(Events::Events&);

		/// <summary> Moves and faces in the given <see cref="Direction"/>. </summary>
		/// <param name="_direction"> The direction in which to move. </param>
		inline void MoveInDirection(const Directions _direction)	{ SetFacing(_direction); m_tilePosition += m_facing.GetNormal(); }

		/// <summary> Sets the <see cref="Direction"/> in which this <see cref="Player"/> is facing. </summary>
		/// <param name="_direction"> The direction in which to face. </param>
		inline void SetFacing(const Directions _direction)			{ m_facing = Direction(_direction); m_spriteID = SpriteData::PlayerLeft + _direction; }

		/// <summary> Gets the <see cref="Direction"/> in which this <see cref="Player"/> is facing. </summary>
		/// <returns> The <see cref="Direction"/> in which this <see cref="Player"/> is facing. </returns>
		inline Direction GetFacing()						const	{ return m_facing; }

		/// <summary> Gets how far the player can see. </summary>
		/// <returns> How far the player can see. </returns>
		inline uint8_t GetSightDistance()					const	{ return m_sightDistance; }

		/// <summary> Gets the player's inventory. </summary>
		/// <returns> The player's inventory. </returns>
		inline Inventory::Inventory& GetInventory()					{ return m_inventory; }
	private:
		/// <summary> The <see cref="Direction"/>. </summary>
		Direction m_facing;

		/// <summary> How many tiles forward the player can see. </summary>
		uint8_t	m_sightDistance;

		/// <summary> The <see cref="Inventory"/> within which the <see cref="WallGem"/>s are stored. </summary>
		Inventory::Inventory m_inventory;

		void minedGem(Events::EventContext*);
	};
}
#endif