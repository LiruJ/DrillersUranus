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

	LetterBoxScreen(LetterBoxScreen&) = delete;
	LetterBoxScreen& operator=(const LetterBoxScreen&) = delete;

	virtual void Resize(int, int);

	/// <summary> Converts a window-space position to a screen-space position. </summary>
	/// <param name="_windowPosition"> The position within the window. </param>
	/// <returns> The converted screen-space position. </returns>
	virtual Point ToScreenSpace(const Point _windowPosition) { return m_position + _windowPosition * m_scale; }

	virtual Point ToWindowSpace(const Point _screenPosition) { return (_screenPosition - m_position) / m_scale; }

	virtual Point	ToScreenSize(const Point _size)		{ return Point(ceil(_size.x * m_scale), ceil(_size.y * m_scale)); }
	virtual int		ToScreenSize(const int _size)		{ return ceil(_size * m_scale); }
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