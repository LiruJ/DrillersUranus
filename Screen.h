#ifndef SCREEN_H
#define SCREEN_H

// Data includes.
#include "Point.h"
#include "Rectangle.h"

// Typedef includes.
#include <stdint.h>

namespace Screens
{
	/// <summary> Represents the area within the window where the game is actually drawn and played. </summary>
	class Screen
	{
	public:
		virtual ~Screen() {};

		/// <summary> Converts a screen-space position to a window-space position. </summary>
		/// <param name="_screenPosition"> The position within the screen. </param>
		/// <returns> The converted window-space position. </returns>
		virtual Point		ScreenToWindowSpace(Point _screenPosition) = 0;

		/// <summary> Converts a window-space position to a screen-space position. </summary>
		/// <param name="_windowPosition"> The position within the window. </param>
		/// <returns> The converted screen-space position. </returns>
		virtual Point		WindowToScreenSpace(Point _windowPosition) = 0;
		
		/// <summary> Converts a screen-space size to a window-space size. </summary>
		/// <param name="_screenSize"> The screen-space size. </param>
		/// <returns> The converted window-space size. </returns>
		virtual Point		ScreenToWindowSize(Point _screenSize) = 0;

		/// <summary> Converts a screen-space size to a window-space size. </summary>
		/// <param name="_screenSize"> The screen-space size. </param>
		/// <returns> The converted window-space size. </returns>
		virtual int32_t		ScreenToWindowSize(int32_t _screenSize) = 0;

		/// <summary> Converts a window-space size to a screen-space size. </summary>
		/// <param name="_windowSize"> The window-space size. </param>
		/// <returns> The converted screen-space size. </returns>
		virtual Point		WindowToScreenSize(Point _windowSize) = 0;

		/// <summary> Converts a window-space size to a screen-space size. </summary>
		/// <param name="_windowSize"> The window-space size. </param>
		/// <returns> The converted screen-space size. </returns>
		virtual int32_t		WindowToScreenSize(int32_t _windowSize) = 0;

		/// <summary> Converts a screen-space boudns to a window-space bounds. </summary>
		/// <param name="_screenBounds"> The screen-space bounds. </param>
		/// <returns> The converted window-space bounds. </returns>
		virtual Rectangle	ScreenToWindowBounds(Rectangle _screenBounds) = 0;

		/// <summary> Converts a window-space bounds to a screen-space bounds. </summary>
		/// <param name="_windowBounds"> The window-space bounds. </param>
		/// <returns> The converted screen-space bounds. </returns>
		virtual Rectangle	WindowToScreenBounds(Rectangle _windowBounds) = 0;

		/// <summary> Gets the scale. </summary>
		/// <returns> The scale. </returns>
		virtual float_t		GetScale() = 0;
	};
}
#endif