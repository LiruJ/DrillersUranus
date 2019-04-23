#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

// Derived includes.
#include "Frame.h"

// Service includes.
#include "Events.h"
#include "EventContext.h"

// Utility includes.
#include <algorithm>

namespace UserInterface
{
	/// <summary> Represents a loading or progress bar. </summary>
	class ProgressBar : public Frame
	{
	public:
		/// <summary> Creates an empty <see cref="ProgressBar"/>. </summary>
		ProgressBar() : Frame::Frame(), m_max(100), m_current(0) {}

		/// <summary> Creates a <see cref="ProgressBar"/> at the given position with the given size and sprite ID. </summary>
		/// <param name="_position"> The position. </param>
		/// <param name="_size"> the size. </param>
		/// <param name="_spriteID"> The sprite ID. </param>
		ProgressBar(const Point _position, const Point _size, const uint16_t _spriteID) : Frame::Frame(_position, _size, _spriteID), m_max(100), m_current(0) {}

		virtual void Draw(Services::ServiceProvider&) const;

		/// <summary> Sets the current value. </summary>
		/// <param name="_value"> The new value. </param>
		void SetValue(const uint32_t _value)	{ m_current =  std::min(m_max, _value); }

		/// <summary> Sets the max value. </summary>
		/// <param name="_max"> The new max value. </param>
		void SetMax(const uint32_t _max)		{ m_max = _max; }
	private:
		/// <summary> The highest value of the bar. </summary>
		uint32_t m_max;

		/// <summary> The current value of the bar. </summary>
		uint32_t m_current;
	};
}
#endif