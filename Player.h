#ifndef PLAYER_H
#define PLAYER_H

// Derived includes.
#include "MapObject.h"

// Data includes.
#include "Direction.h"

namespace GameObjects
{
	/// <summary> Represents the player on the map. </summary>
	class Player : public MapObject
	{
	public:
		/// <summary> Creates a basic <see cref="Player"/>. </summary>
		Player() : MapObject::MapObject(SpriteData::ObjectID::PlayerUp), m_facing(Direction(Directions::Up)) {}

		/// <summary> Moves and faces in the given <see cref="Direction"/>. </summary>
		/// <param name="_direction"> The direction in which to move. </param>
		void MoveInDirection(const Directions _direction) { SetFacing(_direction); m_tilePosition += m_facing.GetNormal(); }

		/// <summary> Sets the <see cref="Direction"/> in which this <see cref="Player"/> is facing. </summary>
		/// <param name="_direction"> The direction in which to face. </param>
		inline void SetFacing(const Directions _direction) { m_facing = Direction(_direction); m_spriteID = SpriteData::PlayerLeft + _direction; }

		/// <summary> Gets the <see cref="Direction"/> in which this <see cref="Player"/> is facing. </summary>
		/// <returns> The <see cref="Direction"/> in which this <see cref="Player"/> is facing. </returns>
		inline Direction GetFacing()						const { return m_facing; }
	private:
		/// <summary> The <see cref="Direction"/>. </summary>
		Direction m_facing;
	};
}
#endif