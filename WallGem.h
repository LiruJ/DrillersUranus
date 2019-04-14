#ifndef WALLGEM_H
#define WALLGEM_H

// Data includes.
#include "Point.h"
#include "Rectangle.h"
#include "GemCollider.h"
#include "WallData.h"

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
		WallGem(const Point _wallPosition, const uint8_t _layer, const SpriteData::GemID _gemID) : m_wallPosition(_wallPosition), m_wallLayer(_layer), m_gemID(_gemID), m_collider(GemCollider::GetGemColliderFromGemID(_gemID)) 
		{
			// Set anything unique to a gem ID.
			switch (_gemID)
			{
			case SpriteData::GemID::Diamond:	{ m_value = 5500; break; }
			case SpriteData::GemID::Emerald:	{ m_value = 950; break; }
			case SpriteData::GemID::Ruby:		{ m_value = 2800; break; }
			case SpriteData::GemID::Sapphire:	{ m_value = 1800; break; }
			default:							{ throw std::exception("Given gem ID is invalid."); }
			}
		}

		void Draw();

		/// <summary> Finds if this <see cref="WallGem"/> is fully covered up by the given <see cref="WallData"/>. </summary>
		/// <param name="_wallData"> The data against which to check. </param>
		/// <returns> <c>true</c> if this <see cref="WallGem"/> is completely covered; otherwise, <c>false</c>. </returns>
		inline bool IsFullyCovered(WallData& _wallData) const { return m_collider.IsFullyCovered(m_wallPosition, m_wallLayer, _wallData); }

		/// <summary> Finds if this <see cref="WallGem"/> is fully uncovered by the given <see cref="WallData"/>. </summary>
		/// <param name="_wallData"> The data against which to check. </param>
		/// <returns> <c>true</c> if this <see cref="WallGem"/> is completely uncovered; otherwise, <c>false</c>. </returns>
		inline bool IsFullyUncovered(WallData& _wallData) const { return m_collider.IsFullyUncovered(m_wallPosition, m_wallLayer, _wallData); }

		/// <summary> Finds if the given position on the cave wall is within this <see cref="WallGem"/>. </summary>
		/// <param name="_wallPosition"> The wall position. </param>
		/// <returns> <c>true</c> if the position collides with this <see cref="WallGem"/>; otherwise, <c>false</c>. </returns>
		inline bool CollidesWith(const Point _wallPosition) const { return m_collider.CollidesWith(_wallPosition - m_wallPosition); }

		/// <summary> Finds if this <see cref="WallGem"/> collides with the given <see cref="WallGem"/>. </summary>
		/// <param name="_other"> The <see cref="WallGem"/> against whcih to check for collisions. </param>
		/// <returns> <c>true</c> if the <see cref="WallGem"/>s collide; otherwise, <c>false</c>. </returns>
		inline bool CollidesWith(const WallGem _other) const { return (m_wallLayer == _other.m_wallLayer) ? m_collider.CollidesWith(_other.m_wallPosition - m_wallPosition, _other.m_collider) : false; }

		/// <summary> Gets the position of this <see cref="WallGem"/>. </summary>
		/// <returns> The position of this <see cref="WallGem"/>. </returns>
		inline Point GetWallPosition() const { return m_wallPosition; }

		/// <summary> Gets the width of this <see cref="WallGem"/>. </summary>
		/// <returns> The width of this <see cref="WallGem"/>. </returns>
		inline uint8_t GetWidth() const { return m_collider.GetWidth(); }

		/// <summary> Gets the height of this <see cref="WallGem"/>. </summary>
		/// <returns> The height of this <see cref="WallGem"/>. </returns>
		inline uint8_t GetHeight() const { return m_collider.GetHeight(); }

		/// <summary> Gets the layer of this <see cref="WallGem"/>. </summary>
		/// <returns> The layer of this <see cref="WallGem"/>. </returns>
		inline uint8_t GetLayer() const { return m_wallLayer; }

		/// <summary> Gets the value of this <see cref="WallGem"/>. </summary>
		/// <returns> The value of this <see cref="WallGem"/>. </returns>
		inline uint16_t GetValue() const { return m_value; }

		/// <summary> Gets the ID of this <see cref="WallGem"/>. </summary>
		/// <returns> The ID of this <see cref="WallGem"/>. </returns>
		inline SpriteData::GemID GetID() const { return m_gemID; }

		/// <summary> Sets the position of this <see cref="WallGem"/>. </summary>
		/// <param name="_wallPosition"> The new wall position. </returns>
		inline void SetWallPosition(const Point _wallPosition) { m_wallPosition = _wallPosition; }
	private:
		/// <summary> The type of <see cref="GemCollider"/> this gem uses. </summary>
		GemCollider			m_collider;

		/// <summary> Where this gem is on the cave wall. </summary>
		Point				m_wallPosition;

		/// <summary> The layer in which this gem resides on the cave wall. </summary>
		uint8_t				m_wallLayer;

		/// <summary> The ID of this gem. </summary>
		SpriteData::GemID	m_gemID;

		/// <summary> The value of this gem. </summary>
		uint16_t			m_value;
	};
}
#endif