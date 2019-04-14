#ifndef GEMCOLLIDER_H
#define GEMCOLLIDER_H

// Data includes.
#include "Point.h"
#include "WallData.h"

// Utility includes.
#include "SpriteData.h"
#include <vector>
#include <utility>

// Typedef includes.
#include <stdint.h>

namespace Minigames
{
	/// <summary> Represents a generic gem collider. </summary>
	class GemCollider
	{
	public:
		/// <summary> Creates and returns the <see cref="GemCollider"/> from a given Gem ID. </summary>
		/// <param name="_gemID"> The ID of the desired gem. </param>
		/// <returns> A <see cref="GemCollider"/> tied to the given ID. </returns>
		static GemCollider GetGemColliderFromGemID(const SpriteData::GemID _gemID)
		{
			switch (_gemID)
			{
			case SpriteData::GemID::Ruby: { return GemCollider(5, 5, s_colliders.m_rubyCollider); break; }
			case SpriteData::GemID::Diamond: { return GemCollider(5, 4, s_colliders.m_diamondCollider); break; }
			case SpriteData::GemID::Sapphire: { return GemCollider(9, 9, s_colliders.m_sapphireCollider); break; }
			case SpriteData::GemID::Emerald: { return GemCollider(10, 10, s_colliders.m_emeraldCollider); break; }
			default: { throw std::exception("Given gem ID was invalid."); break; }
			}
		}

		/// <summary> Finds if the given position collides with this collider. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the position collides; otherwise, <c>false</c>. </returns>
		inline bool		CollidesWith(const Point _position) const { return (Rectangle(0, 0, m_width, m_height).IsPointInside(_position)) ? (_position.y >= getColumnStart(_position.x) && _position.y < getColumnStart(_position.x) + getColumnHeight(_position.x)) : false; }

		bool			CollidesWith(Point, GemCollider) const;

		bool			IsFullyCovered(Point, uint8_t, WallData&) const;

		bool			IsFullyUncovered(Point, uint8_t, WallData&) const;

		/// <summary> Gets the width of this collider. </summary>
		/// <returns> The width of this collider. </returns>
		inline uint8_t	GetWidth() const { return m_width; }

		/// <summary> Gets the height of this collider. </summary>
		/// <returns> The height of this collider. </returns>
		inline uint8_t	GetHeight() const { return m_height; }
	private:
		/// <summary> Creates a gem collider with the given width, height, and data. </summary>
		/// <param name="_width"> The width. </param>
		/// <param name="_height"> The height. </param>
		/// <param name="_data"> The data. </param>
		GemCollider(const uint8_t _width, const uint8_t _height, std::vector<std::pair<uint8_t, uint8_t>>& _data) : m_width(_width), m_height(_height), m_columnStartsAndHeights(&_data) {}

		/// <summary> The width of the collider. </summary>
		uint8_t m_width;

		/// <summary> The height of the collider. </summary>
		uint8_t m_height;

		/// <summary> The list of pairs, with the first being the starting position of a column, and the second being a height. </summary>
		std::vector<std::pair<uint8_t, uint8_t>>* m_columnStartsAndHeights;

		/// <summary> Gets the starting position of a column from the given x position. </summary>
		/// <param name="_xPosition"> The x position. </param>
		/// <returns> The starting position of a column from the given x position. </returns>
		inline uint8_t getColumnStart(const uint8_t _xPosition) const { return (*m_columnStartsAndHeights)[_xPosition].first; }

		/// <summary> Gets the height of a column from the given x position. </summary>
		/// <param name="_xPosition"> The x position. </param>
		/// <returns> The height of a column from the given x position. </returns>
		inline uint8_t getColumnHeight(const uint8_t _xPosition) const { return (*m_columnStartsAndHeights)[_xPosition].second; }

		/// <summary> Represents the colliders for each gem. </summary>
		class colliders
		{
		public:
			/// <summary> The collider for a ruby. </summary>
			std::vector<std::pair<uint8_t, uint8_t>> m_rubyCollider
			{
				std::pair<uint8_t, uint8_t> { 2, 2 },
				std::pair<uint8_t, uint8_t> { 1, 4 },
				std::pair<uint8_t, uint8_t> { 0, 5 },
				std::pair<uint8_t, uint8_t> { 0, 4 },
				std::pair<uint8_t, uint8_t> { 0, 3 },
			};

			/// <summary> The collider for a diamond. </summary>
			std::vector<std::pair<uint8_t, uint8_t>> m_diamondCollider
			{
				std::pair<uint8_t, uint8_t> { 1, 1 },
				std::pair<uint8_t, uint8_t> { 0, 3 },
				std::pair<uint8_t, uint8_t> { 0, 4 },
				std::pair<uint8_t, uint8_t> { 0, 3 },
				std::pair<uint8_t, uint8_t> { 1, 1 },
			};

			/// <summary> The collider for a sapphire. </summary>
			std::vector<std::pair<uint8_t, uint8_t>> m_sapphireCollider
			{
				std::pair<uint8_t, uint8_t> { 3, 3 },
				std::pair<uint8_t, uint8_t> { 2, 5 },
				std::pair<uint8_t, uint8_t> { 1, 7 },
				std::pair<uint8_t, uint8_t> { 0, 9 },
				std::pair<uint8_t, uint8_t> { 0, 9 },
				std::pair<uint8_t, uint8_t> { 0, 9 },
				std::pair<uint8_t, uint8_t> { 1, 7 },
				std::pair<uint8_t, uint8_t> { 2, 5 },
				std::pair<uint8_t, uint8_t> { 3, 3 },
			};

			/// <summary> The collider for an emerald. </summary>
			std::vector<std::pair<uint8_t, uint8_t>> m_emeraldCollider
			{
				std::pair<uint8_t, uint8_t> { 5, 2 },
				std::pair<uint8_t, uint8_t> { 4, 4 },
				std::pair<uint8_t, uint8_t> { 3, 6 },
				std::pair<uint8_t, uint8_t> { 2, 8 },
				std::pair<uint8_t, uint8_t> { 1, 9 },
				std::pair<uint8_t, uint8_t> { 0, 9 },
				std::pair<uint8_t, uint8_t> { 0, 8 },
				std::pair<uint8_t, uint8_t> { 1, 6 },
				std::pair<uint8_t, uint8_t> { 2, 4 },
				std::pair<uint8_t, uint8_t> { 3, 2 },
			};
		};

		/// <summary> Statically creates the list of the different types of gem colliders. </summary>
		static colliders s_colliders;
	};
}

#endif