#include "LetterBoxScreen.h"

void LetterBoxScreen::Resize(const int _newX, const int _newY)
{
	// Divide the new screen size by the aspect ratio.
	float ratioX = _newX / (float)c_aspectRatio.x;
	float ratioY = _newY / (float)c_aspectRatio.y;

	// Resize the output, rescale, and reposition based on the smallest dimension of the screen relative to the aspect ratio.
	if (ratioX < ratioY)
	{
		m_size = Point((float_t)_newX, ratioX * c_aspectRatio.y);
		m_scale = ratioX / (c_designDimensions.x / c_aspectRatio.x);
		m_position = Point(0, (_newY - m_size.y) / 2);
	}
	else
	{
		m_size = Point(ratioY * c_aspectRatio.x, (float_t)_newY);
		m_scale = ratioY / (c_designDimensions.y / c_aspectRatio.y);
		m_position = Point((_newX - m_size.x) / 2, 0);
	}
}