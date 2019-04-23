#ifndef LETTERBOXSCREEN_H
#define LETTERBOXSCREEN_H

// Derived includes.
#include "Screen.h"

// Service includes.
#include "Time.h"

// Utility includes.
#include <math.h>

namespace Screens
{
	/// <summary> Represents a forced 16:9 aspect ratio screen at 960x540. </summary>
	class LetterBoxScreen : public Screen
	{
	public:
		LetterBoxScreen() : m_offset(0, 0), m_currentStrength(0), m_currentDirection(0) { Resize(c_designDimensions.x, c_designDimensions.y); }

		virtual Point		ScreenToWindowSpace(const Point _screenPosition)	{ return (m_position + m_offset) + (_screenPosition * m_scale); }

		virtual Point		WindowToScreenSpace(const Point _windowPosition)	{ return ((_windowPosition + m_offset) - m_position) / m_scale; }

		virtual Point		ScreenToWindowSize(const Point _screenSize)			{ return Point(ceil((float_t)_screenSize.x * m_scale), ceil((float_t)_screenSize.y * m_scale)); }

		virtual int32_t		ScreenToWindowSize(const int32_t _screenSize)		{ return (int32_t)ceil(_screenSize * m_scale); }

		virtual Point		WindowToScreenSize(const Point _windowSize)			{ return Point(ceil((float_t)_windowSize.x / m_scale), ceil((float_t)_windowSize.y / m_scale)); }

		virtual int32_t		WindowToScreenSize(const int32_t _windowSize)		{ return (int32_t)ceil(_windowSize / m_scale); }

		virtual Rectangle	ScreenToWindowBounds(const Rectangle _screenBounds) { return Rectangle(ScreenToWindowSpace(Point(_screenBounds.x, _screenBounds.y)), ScreenToWindowSize(Point(_screenBounds.w, _screenBounds.h))); }

		virtual Rectangle	WindowToScreenBounds(const Rectangle _windowBounds) { return Rectangle(WindowToScreenSpace(Point(_windowBounds.x, _windowBounds.y)), WindowToScreenSize(Point(_windowBounds.w, _windowBounds.h))); }

		virtual float_t		GetScale()											{ return m_scale; }

		virtual void		ShakeScreen(uint16_t);

		void				Update(Time::Time&);

		void				Resize(int32_t, int32_t);
	private:
		/// <summary> The dimensions of the screen the game was designed for. </summary>
		const Point		c_designDimensions = Point(960, 540);

		/// <summary> The aspect ratio of the screen the game was designed for. </summary>
		const Point		c_aspectRatio = Point(16, 9);

		/// <summary> The minimum strength in pixels before the screen stops shaking. </summary>
		const float_t	c_minimumStrength = 2.0f;

		/// <summary> The multiplier of how much strength is lost per second while shaking. </summary>
		const float_t	c_strengthDecay = 3.5f;

		/// <summary> The position of the screen. </summary>
		Point			m_position;

		/// <summary> The size of the screen. </summary>
		Point			m_size;

		/// <summary> The scale from the original design dimensions to the actual screen size. </summary>
		float_t			m_scale;

		/// <summary> The offset of the screen due to the screen shake. </summary>
		Point			m_offset;

		/// <summary> The current strength of the screen shake in pixels from the centre. </summary>
		float_t			m_currentStrength;

		/// <summary> The current direction of the screen shake in radians. </summary>
		float_t			m_currentDirection;
	};
}
#endif