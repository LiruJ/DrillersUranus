#ifndef FRAME_H
#define FRAME_H

// Data includes.
#include "Point.h"
#include "Rectangle.h"

// Service includes.
#include "ServiceProvider.h"

// Typedef includes.
#include <stdint.h>

namespace UserInterface
{
	/// <summary> Represents a plain UI frame with no extra behaviour. </summary>
	class Frame
	{
	public:
		/// <summary> Creates an empty <see cref="Frame"/>. </summary>
		Frame() : m_position(Point(0, 0)), m_size(Point(0, 0)), m_bounds(Rectangle(0, 0, 0, 0)), m_spriteID(0), m_isActive(true) {}

		/// <summary> Creates a <see cref="Frame"/> at the given position with the given size and sprite ID. </summary>
		/// <param name="_position"> The position. </param>
		/// <param name="_size"> the size. </param>
		/// <param name="_spriteID"> The sprite ID. </param>
		Frame(const Point _position, const Point _size, const uint16_t _spriteID) : m_position(_position), m_size(_size), m_bounds(_position, _size), m_spriteID(_spriteID), m_isActive(true) {}

		virtual void Draw(Services::ServiceProvider& _services) const;

		/// <summary> Gets if this <see cref="Frame"/> is updated and drawn. </summary>
		/// <returns> If this <see cref="Frame"/> is active. </returns>
		virtual bool IsActive() { return m_isActive; }

		/// <summary> Sets the active status of this <see cref="Frame"/>. </summary>
		/// <param name="_active"> The new active status. </param>
		virtual void SetActive(const bool _active) { m_isActive = _active; }

		virtual void SetPosition(const Point _position) { m_position = _position; m_bounds = Rectangle(_position, m_size); }
	protected:
		/// <summary> The ID of the sprite that should be drawn. </summary>
		uint16_t	m_spriteID;

		/// <summary> <c>true</c> if this element should be drawn and updated; otherwise, <c>false</c>. </summary>
		bool		m_isActive;

		/// <summary> The position. </summary>
		Point		m_position;

		/// <summary> The size. </summary>
		Point		m_size;

		/// <summary> The bounds. </summary>
		Rectangle	m_bounds;
	};
}
#endif