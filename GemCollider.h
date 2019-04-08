#ifndef GEMCOLLIDER_H
#define GEMCOLLIDER_H

// Data includes.
#include "Point.h"
#include "Rectangle.h"

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
		static GemCollider GetGemColliderFromGemID(const SpriteData::GemID _gemID)
		{
			switch (_gemID)
			{ 
			case SpriteData::GemID::Ruby: { return GemCollider(5, 5, s_colliders.m_rubyCollider); break; }
			case SpriteData::GemID::Diamond: { return GemCollider(5, 4, s_colliders.m_diamondCollider); break; }
			default: { throw std::exception("Given gem ID was invalid."); break; }
			}
		}

		/// <summary> Finds if the given position collides with this collider. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the position collides; otherwise, <c>false</c>. </returns>
		inline bool CollidesWith(const Point _position) const { return (Rectangle(0, 0, m_width, m_height).IsPointInside(_position)) ? (_position.y > getColumnStart(_position.x) && _position.y < getColumnStart(_position.x) + getColumnHeight(_position.x)) : false; }
	private:
		/// <summary> Creates a gem collider with the given width, height, and data. </summary>
		/// <param name="_width"> The width. </param>
		/// <param name="_height"> The height. </param>
		/// <param name="_data"> The data. </param>
		GemCollider(const uint8_t _width, const uint8_t _height, std::vector<std::pair<uint8_t, uint8_t>>& _data) : m_width(_width), m_height(_height), m_columnStartsAndHeights(_data) {}

		/// <summary> The width of the collider. </summary>
		uint8_t m_width;

		/// <summary> The height of the collider. </summary>
		uint8_t m_height;

		/// <summary> The list of pairs, with the first being the starting position of a column, and the second being a height. </summary>
		std::vector<std::pair<uint8_t, uint8_t>>& m_columnStartsAndHeights;

		/// <summary> Gets the starting position of a column from the given x position. </summary>
		/// <param name="_xPosition"> The x position. </param>
		/// <returns> The starting position of a column from the given x position. </returns>
		uint8_t getColumnStart(const uint8_t _xPosition) const { return m_columnStartsAndHeights[_xPosition].first; }

		/// <summary> Gets the height of a column from the given x position. </summary>
		/// <param name="_xPosition"> The x position. </param>
		/// <returns> The height of a column from the given x position. </returns>
		uint8_t getColumnHeight(const uint8_t _xPosition) const { return m_columnStartsAndHeights[_xPosition].second; }

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
		};

		/// <summary> Statically creates the list of the different types of gem colliders. </summary>
		static colliders s_colliders;
	};
}

#endif