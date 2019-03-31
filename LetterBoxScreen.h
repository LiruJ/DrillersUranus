#ifndef LETTERBOXSCREEN_H
#define LETTERBOXSCREEN_H

// Graphical includes.
#include "Screen.h"

// Data includes.
#include "Point.h"
#include <math.h>

class LetterBoxScreen : public Screen
{
public:
	LetterBoxScreen() { Resize(c_designDimensions.x, c_designDimensions.y); }
	
	/// <summary> Converts a window-space position to a screen-space position. </summary>
	/// <param name="_windowPosition"> The position within the window. </param>
	/// <returns> The converted screen-space position. </returns>
	virtual Point WindowToScreenSpace(const Point _windowPosition)	{ return m_position + _windowPosition * m_scale; }

	virtual Point ScreenToWindowSpace(const Point _screenPosition)	{ return (_screenPosition - m_position) / m_scale; }

	virtual Point	WindowToScreenSize(const Point _size)			{ return Point(ceil((float_t)_size.x * m_scale), ceil((float_t)_size.y * m_scale)); }
	virtual int		WindowToScreenSize(const int32_t _size)			{ return (int32_t)ceil(_size * m_scale); }

	virtual void Resize(int32_t, int32_t);
private:
	/// <summary> The dimensions of the screen the game was designed for. </summary>
	const Point c_designDimensions = Point(960, 540);

	/// <summary> The aspect ratio of the screen the game was designed for. </summary>
	const Point c_aspectRatio = Point(16, 9);

	/// <summary> The position of the screen. </summary>
	Point			m_position;

	/// <summary> The size of the screen. </summary>
	Point			m_size;

	/// <summary> The scale from the original design dimensions to the actual screen size. </summary>
	float			m_scale;
};

#endif