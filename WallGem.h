#ifndef WALLGEM_H
#define WALLGEM_H

// Data includes.
#include "Point.h"
#include "Rectangle.h"
#include "GemCollider.h"

// Utility includes.
#include "SpriteData.h"

// Typedef includes.
#include <stdint.h>

namespace Minigames
{
	/// <summary> Represents a gem found in the cave wall minigame. </summary>
	class WallGem
	{
	public:
		/// <summary> Creates a <see cref="WallGem"/> at the given position with the given gem ID. </summary>
		/// <param name="_wallPosition"> The position within the cave wall. </param>
		/// <param name="_layer"> The layer within the cave wall. </param>
		/// <param name="_gemID"> The gem ID. </param>
		WallGem(const Point _wallPosition, const uint8_t _layer, const SpriteData::GemID _gemID) : m_wallPosition(_wallPosition), m_wallLayer(_layer), m_gemID(_gemID), m_collider(GemCollider::GetGemColliderFromGemID(_gemID)) {}

		bool IsFullyCovered();

		/// <summary> Finds if the given position on the cave wall is within this gem. </summary>
		/// <param name="_wallPosition"> The wall position. </param>
		/// <returns> <c>true</c> if the position collides with the gem; otherwise, <c>false</c>. </returns>
		inline bool CollidesWith(const Point _wallPosition) const { return m_collider.CollidesWith(_wallPosition - m_wallPosition); }
	private:
		/// <summary> Where this gem is on the cave wall. </summary>
		Point m_wallPosition;

		/// <summary> The layer in which this gem resides on the cave wall. </summary>
		uint8_t m_wallLayer;

		/// <summary> The type of <see cref="GemCollider"/> this gem uses. </summary>
		GemCollider m_collider;

		/// <summary> The ID of this gem. </summary>
		SpriteData::GemID m_gemID;
	};
}
#endif