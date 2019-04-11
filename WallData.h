#ifndef WALLDATA_H
#define WALLDATA_H

// Data includes.
#include "Rectangle.h"
#include "Point.h"

// Utility includes.
#include <vector>

// Typedef includes.
#include <stdint.h>
#include <cmath>

namespace Minigames
{
	/// <summary> Represents the data for the wall in the mining minigame. </summary>
	class WallData
	{
	public:
		WallData(uint8_t, uint8_t);

		void Generate();

		/// <summary> Gets the value of the data at the given position. </summary>
		/// <param name="_x"> The x of the position. </param>
		/// <param name="_y"> The y of the position. </param>
		/// <returns> The value of the data at the given position. </returns>
		inline uint8_t GetValueAt(const uint8_t _x, const uint8_t _y)				const	{ return (IsInRange(_x, _y)) ? m_data[_x][_y] : 0; }

		/// <summary> Gets the value of the data at the given position. </summary>
		/// <param name="_position"> The position. </param>
		/// <returns> The value of the data at the given position. </returns>
		inline uint8_t GetValueAt(const Point _position)							const	{ return (IsInRange(_position)) ? m_data[_position.x][_position.y] : 0; }

		/// <summary> Sets the value of the data at the given position to the given value. </summary>
		/// <param name="_x"> The x of the position. </param>
		/// <param name="_y"> The y of the position. </param>
		/// <param name="_value"> The value to set. </param>
		inline void SetValueAt(const uint8_t _x, const uint8_t _y, const uint8_t _value)	{ if (IsInRange(_x, _y)) { m_data[_x][_y] = _value;} }

		/// <summary> Finds if the given position is in range of the data. </summary>
		/// <param name="_x"> The x of the position. </param>
		/// <param name="_y"> The y of the position. </param>
		/// <returns> <c>true</c> if the given position is in range; otherwise, <c>false</c>. </returns>
		inline bool IsInRange(const uint8_t _x, const uint8_t _y)					const	{ return m_bounds.IsPointInside(Point(_x, _y)); }

		/// <summary> Finds if the given position is in range of the data. </summary>
		/// <param name="_position"> The position. </param>
		/// <returns> <c>true</c> if the given position is in range; otherwise, <c>false</c>. </returns>
		inline bool IsInRange(const Point _position)								const	{ return m_bounds.IsPointInside(_position); }

		/// <summary> Gets the width of the data. </summary>
		/// <returns> The width of the data. </returns>
		inline uint8_t GetWidth()													const	{ return m_width; }

		/// <summary> Gets the height of the data. </summary>
		/// <returns> The height of the data. </returns>
		inline uint8_t GetHeight()													const	{ return m_height; }
	private:
		/// <summary> The maximum value possible. </summary>
		const uint8_t	c_maxValue = 13;

		/// <summary> The maximum value possible. </summary>
		const uint8_t	c_minValue = 3;

		/// <summary> The chance for a bump to go down one layer, set really low as this is rolled a lot. <c>0</c> for no chance, <c>1</c> for full chance. </summary>
		const float_t	c_downChance = 0.001f;

		/// <summary> The most attempts that will be made to place a tile at a given layer. </summary>
		const uint16_t	c_maxAttempts = 20000;

		/// <summary> The width of the data. </summary>
		uint8_t			m_width;
		
		/// <summary> The height of the data. </summary>
		uint8_t			m_height;

		/// <summary> The bounds of the data. </summary>
		Rectangle		m_bounds;

		/// <summary> The data itself. </summary>
		std::vector<std::vector<uint8_t>> m_data;
		
		void reset();

		void generateBump(uint8_t);
	};
}
#endif