#ifndef SCREEN_H
#define SCREEN_H

// Data includes.
#include "Point.h"

// Typedef includes.
#include <stdint.h>

class Screen
{
public:
	virtual ~Screen() {};

	virtual Point	WindowToScreenSpace(Point) = 0;
	virtual Point	ScreenToWindowSpace(Point) = 0;

	virtual Point	WindowToScreenSize(Point) = 0;
	virtual int		WindowToScreenSize(int32_t) = 0;

	virtual void	Resize(int32_t, int32_t) = 0;
};

#endif