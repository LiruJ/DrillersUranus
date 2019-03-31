#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "Frame.h"

#include <algorithm>

namespace UserInterface
{
	class ProgressBar : public Frame
	{
	public:
		ProgressBar() : Frame::Frame(), m_max(100), m_current(0) {}
		ProgressBar(const Point _position, const Point _size, const uint16_t _spriteID) : Frame::Frame(_position, _size, _spriteID), m_max(100), m_current(0) {}

		virtual void Draw();

		void SetValue(const uint32_t _value)	{ m_current =  std::min(m_max, _value); }
		void SetMax(const uint32_t _max)		{ m_max = _max; }

	private:
		/// <summary> The highest value of the bar. </summary>
		uint32_t m_max;

		/// <summary> The current value of the bar. </summary>
		uint32_t m_current;
	};
}
#endif