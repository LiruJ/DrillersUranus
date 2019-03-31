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
		ProgressBar(const Point _position, const Point _size, const unsigned short _spriteID) : Frame::Frame(_position, _size, _spriteID), m_max(100), m_current(0) {}

		virtual void Draw();

		void SetValue(const unsigned int _value)	{ m_current =  std::min(m_max, _value); }
		void SetMax(const unsigned int _max)		{ m_max = _max; }

	private:
		/// <summary> The highest value of the bar. </summary>
		unsigned int m_max;

		/// <summary> The current value of the bar. </summary>
		unsigned int m_current;
	};
}
#endif